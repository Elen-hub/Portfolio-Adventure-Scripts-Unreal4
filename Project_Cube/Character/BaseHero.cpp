// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHero.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SprintFunction.h"
#include "StatFunction.h"
#include "PlayerCameraFunction.h"
#include "Project_Cube/GameInstance/MainGameInstance.h"
#include "Components/SphereComponent.h"
#include "Project_Cube/Object/BaseWeapon.h"
#include "Project_Cube/Object/Bullet.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Stat.h"
#include "Project_Cube/GameInstance/UIMng.h"
#include "Project_Cube/UI/MainUI.h"

ABaseHero::ABaseHero()
{
	PrimaryActorTick.bCanEverTick = true;

	FStringClassReference classRef("Blueprint'/Game/TestContent/Bullet_BP.Bullet_BP_C'");
	mBulletRefClass = classRef.TryLoadClass<AActor>();

	USpringArmComponent* springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	springArm->SetupAttachment(GetRootComponent());
	springArm->TargetArmLength = 300;
	springArm->SocketOffset = (FVector(0, 50.f, 100.f));
	springArm->bUsePawnControlRotation = true;

	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;

	mPlayerCamera = CreateDefaultSubobject<UPlayerCameraFunction>(TEXT("PlayerCamera"))->Init(springArm, camera);
	mSprintFunction =CreateDefaultSubobject<USprintFunction>(TEXT("Function"))->Init();

	mOverlapCollision->SetSphereRadius(System::InteractDefaultVolumeRange);
	mOverlapCollision->SetHiddenInGame(false);
	TMaxStamina = 100.f;
	TRecoveryStamina =10.f;
}

void ABaseHero::BeginPlay()
{
	Super::BeginPlay();

	FCharacterInformation* info = new FCharacterInformation();
	FCombatStat* stat = new FCombatStat();
	stat->HP = 100.f;
	stat->SP = 100.f;

	mStatFunction->Init(info, stat);

	UMainGameInstance* mainGameInstance = GetGameInstance<UMainGameInstance>();
	mainGameInstance->MainCharacter = this;
	mainGameInstance->UIMng->Open<UMainUI>(EUIType::MainUI)->Enabled(this);

	mPlayerCamera->Set(this, mainGameInstance);
}

void ABaseHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 리로드, 사격중엔 스프린트 사용제약
	mSprintFunction->SetPossibleSprint(!mbIsReloading && !mbIsFire);

	if (mWeapon)
	{
		// 연사딜레이감소
		if (mAutoFireDelay > 0)
			mAutoFireDelay -= DeltaTime;

		// 다음 사격시까시 반동Lerp 적용
		if (mAutoFireDelay > 0)
		{
			const float percent = PERCENT(mElapsedRecoil, mWeapon->FullAutoSpeed);
			mPlayerCamera->SetRebound(FMath::Lerp(0.f, mTargetVerticalRecoil, percent), FMath::Lerp(0.f, mTargetHorizonRecoil, percent));
			mElapsedRecoil += DeltaTime;
		}

		if (mbIsFire)
		{
			// 딜레이체크
			if (mAutoFireDelay > 0)
				return;

			Fire();
		}
		else
		{
			// 자연반동감소
			mCurrRecoil = FMath::Clamp(mCurrRecoil - DeltaTime * 100, 0.f, mWeapon->MaxRecoil);
		}
		if (mbIsReloading)
		{
			mReloadTargetTime -= DeltaTime;
			if (mReloadTargetTime <= 0)
			{
				mbIsReloading = false;
				mReloadTargetTime = 0;
				// 총알을 가져옴
				// 임시
				mWeapon->CurrMagazine = mWeapon->MaxMagazine;
			}
		}
	}
}

void ABaseHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ABaseHero::AttackStart);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ABaseHero::AttackEnd);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ABaseHero::Reload);
	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &ABaseHero::Interaction);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABaseHero::Jump);
	PlayerInputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &ABaseHero::GetItem);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, mSprintFunction, &USprintFunction::SprintActivate);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, mSprintFunction, &USprintFunction::SprintDeactivate);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &ABaseHero::MoveSide);
	PlayerInputComponent->BindAxis("MouseX", mPlayerCamera, &UPlayerCameraFunction::CameraMoveSide);
	PlayerInputComponent->BindAxis("MouseY", mPlayerCamera, &UPlayerCameraFunction::CameraMoveUp);
	PlayerInputComponent->BindAxis("MouseWheel", mPlayerCamera, &UPlayerCameraFunction::CameraLook);
}

void ABaseHero::GetItem()
{
	AItem* item = mPlayerCamera->GetItemLookCrosshair();
	if (item == nullptr)
		return;

	// 리로드 캔슬
	if (mbIsReloading)
	{
		mReloadTargetTime = 0;
		mbIsReloading = false;
	}

	switch (item->GetItemType())
	{
	case EItemType::EIT_AssaultRifle:
	case EItemType::EIT_Pistol:
	case EItemType::EIT_Shotgun:
		SetWeapon(Cast<ABaseWeapon>(item));
		break;
	case EItemType::EIT_Bullet:
	case EItemType::EIT_Potion:
	case EItemType::EIT_Other:
		break;
	default:
		;
	}
}
void ABaseHero::SetWeapon(ABaseWeapon* weapon)
{
	const USkeletalMeshSocket* RightHandSocket = GetMesh()->GetSocketByName("RightHandSocket");
	if (mWeapon != nullptr)
	{
		mWeapon->ActivateCollision(true);
	}

	// 무기관리상태 초기화
	mAutoFireDelay = 0;
	mCurrRecoil = 0;

	// Get weapon
	weapon->ActivateCollision(false);
	RightHandSocket->AttachActor(weapon, GetMesh());
	mWeapon = weapon;
}

void ABaseHero::AttackStart()
{
	if (!mWeapon)
		return;

	if (mWeapon->CurrMagazine <= 0)
	{
		// 총알이 없을경우
		Reload();
		return;
	}
	// 스프린트 해제
	if (mSprintFunction->GetUseSprint())
		mSprintFunction->Deactivate();

	mbIsFire = true;
}

void ABaseHero::AttackEnd()
{
	mbIsFire = false;
}

void ABaseHero::Fire()
{
	if (!mWeapon)
	{
		mbIsFire = false;
		return;
	}
	if (mbIsReloading)
	{
		// 재장전 중일경우
		mbIsFire = false;
		return;
	}
	if (mWeapon->CurrMagazine <= 0)
	{
		// 총알이 없을경우
		mbIsFire = false;
		return;
	}
	// 총알발사
	ABullet* bullet = GetGameInstance<UMainGameInstance>()->SpawnMng->SpawnActor<ABullet>(mBulletRefClass);
	bullet->Enabled(mPlayerCamera->GetMuzzlePos(), mPlayerCamera->GetMuzzleRot(), 0, 10, 0.1f);
	mWeapon->CurrMagazine -= 1;

	// 딜레이적용
	mAutoFireDelay = mWeapon->FullAutoSpeed;

	// 반동Lerp 초기화
	mElapsedRecoil = 0;

	// 반동반영
	mCurrRecoil = FMath::Clamp(mCurrRecoil + mWeapon->Recoil, 0.f, mWeapon->MaxRecoil);
	mTargetVerticalRecoil = -FMath::RandRange(mCurrRecoil * 0.5f, mCurrRecoil);
	mTargetHorizonRecoil = FMath::RandRange(-mCurrRecoil, mCurrRecoil) * 0.5f;

	// 애니메이션 몽타주 설정
	mAnimInstance->Montage_Play(mCombatMontage, 3.0f);
	mAnimInstance->Montage_JumpToSection(FName("Fire"), mCombatMontage);
}
void ABaseHero::Reload()
{
	if (!mWeapon)
		return;
	if (mWeapon->MaxMagazine == mWeapon->CurrMagazine)
		return;
	// 인벤토리에 총알이 없어도 리턴
	if (mbIsReloading)
		return;

	// 스프린트 해제
	if (mSprintFunction->GetUseSprint())
		mSprintFunction->Deactivate();

	mbIsReloading = true;
	mReloadTargetTime = mWeapon->ReloadSpeed;

	// 애니메이션 몽타주 설정
	mAnimInstance->Montage_Play(mCombatMontage, 1.0f);
	mAnimInstance->Montage_JumpToSection(FName("Reload"), mCombatMontage);
}
void ABaseHero::Interaction()
{

}
void ABaseHero::MoveForward(float axis)
{
	TSpeed = 400.f;

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	if (axis < 0)
		axis *= 0.4f;
	else
	{
		if (mbIsFire)
		{
			TSpeed = 400.f;
		}
		else if (mSprintFunction->GetUseSprint())
			TSpeed = 800.f;
	}

	TInputVector.X = axis * TSpeed;
	SetActorRotation(yawRotation);
	AddMovementInput(Direction, axis);
}
void ABaseHero::MoveSide(float axis)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	axis *= 0.6f;

	TInputVector.Y = axis * TSpeed;
	AddMovementInput(Direction, axis);
}
void ABaseHero::Jump()
{
	Super::Jump();
}
