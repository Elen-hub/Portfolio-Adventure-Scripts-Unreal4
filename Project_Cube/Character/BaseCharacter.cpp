// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatFunction.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mStatFunction = CreateDefaultSubobject<UStatFunction>(TEXT("Stat"));

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(GetRootComponent());

	// 오버랩콜리전 기본설정 ( 충돌이벤트 사용안함, 충돌관계 모두 무시 )
	mOverlapCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Collision"));
	mOverlapCollision->SetupAttachment(GetRootComponent());
	mOverlapCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mOverlapCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	mOverlapCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// 캐릭터가 움직인 방향으로 정면을 향함
	GetCharacterMovement()->bOrientRotationToMovement = false;
	// Yaw 540속도로 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	// 점프 힘
	GetCharacterMovement()->JumpZVelocity = 500.f;
	// 공중컨트롤
	GetCharacterMovement()->AirControl = 0.2f;

	TInputVector = FVector(0.f);
}
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	TestInitPos = GetActorLocation();
}
void ABaseCharacter::SetCharacterState(const ECharacterState nextState)
{
	mCharacterState = nextState;
}
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 경직시간 갱신
	if (mbIsHit) mHitElapsedTime += DeltaTime;

	// 이동속도 갱신
	GetCharacterMovement()->MaxWalkSpeed = TSpeed;
	// mFunctionToStateMap[mCharacterState]->OnStateStay;
}

void ABaseCharacter::SetDamage(float damage)
{
	if (mCharacterState == ECharacterState::ECS_Death)
		return;

	if (mStatFunction->SetDamage(damage))
		SetCharacterState(ECharacterState::ECS_Death);
}

void ABaseCharacter::SetHitTime(float hitTime)
{
	// 적용중인 경직시간이 갱신할 시간보다 길다면 리턴
	if (mbIsHit && hitTime > mHitTargetTime - mHitElapsedTime)
		return;

	mHitTargetTime = hitTime;
	mbIsHit = true;
}

void ABaseCharacter::SetNuckback(float force)
{

}

void ABaseCharacter::Death()
{
	mTarget = nullptr;
	mMesh->SetGenerateOverlapEvents(false);
	mOverlapCollision->SetGenerateOverlapEvents(false);
}
