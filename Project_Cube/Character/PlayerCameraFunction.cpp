#include "PlayerCameraFunction.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacter.h"
#include "Project_Cube/Object/Item.h"
#include "Project_Cube/Object/InteractionObject.h"
#include "Project_Cube/GameInstance/MainGameInstance.h"
#include "Project_Cube/UI/MainUI.h"
#include "Project_Cube/UI/MainUI_ItemText.h"
#include "Project_Cube/Character/BaseCharacter.h"

UPlayerCameraFunction::UPlayerCameraFunction()
{
	PrimaryComponentTick.bCanEverTick = true;

	TMouseAxis = 65.f;
}

UPlayerCameraFunction* UPlayerCameraFunction::Init(USpringArmComponent* springArm, UCameraComponent* camera)
{
	mCamera = camera;
	mCameraSpringArm = springArm;
	return this;
}

void UPlayerCameraFunction::Set(ABaseCharacter* character , UMainGameInstance* gameInstance)
{
	mTargetCharacter = character;
	mMainGameInstance = gameInstance;
}

void UPlayerCameraFunction::SetRebound(const float pitch, const float yaw)
{
	mTargetCharacter->AddControllerPitchInput(pitch * GetWorld()->GetDeltaSeconds());
	mTargetCharacter->AddControllerYawInput(yaw* GetWorld()->GetDeltaSeconds());
}

// ũ�ν����� ���̴� �浹������Ʈ�� ��� ����Լ�
TArray<FHitResult> UPlayerCameraFunction::GetHitResultLookCrosshair()
{
	const FVector& worldStartP = mCamera->GetComponentLocation();
	FVector worldEndP = worldStartP + mCamera->GetForwardVector() * (mCameraSpringArm->TargetArmLength + 200.f);
	TArray<FHitResult> HitInfo;
	FCollisionQueryParams queryParams;
	FCollisionObjectQueryParams objectParams = FCollisionObjectQueryParams::AllDynamicObjects;
	GetWorld()->LineTraceMultiByObjectType(HitInfo, worldStartP, worldEndP, objectParams, queryParams);
	return HitInfo;
}

// ũ�ν����� ���̴� ù��° �������� ��� �Լ�
AItem* UPlayerCameraFunction::GetItemLookCrosshair()
{
	const FVector& worldStartP = mCamera->GetComponentLocation();
	FVector worldEndP = worldStartP + mCamera->GetForwardVector() * (mCameraSpringArm->TargetArmLength + 200.f);
	TArray<FHitResult> HitInfo;
	FCollisionQueryParams queryParams;
	FCollisionObjectQueryParams objectParams = FCollisionObjectQueryParams::AllDynamicObjects;
	if (GetWorld()->LineTraceMultiByObjectType(HitInfo, worldStartP, worldEndP, objectParams, queryParams))
	{
		for (FHitResult result : HitInfo)
		{
			if (AItem* item = Cast<AItem>(result.GetActor()))
				return item;
		}
	}
	return nullptr;
}
FVector UPlayerCameraFunction::GetMuzzlePos()
{
	return mCamera->GetComponentLocation() + mCamera->GetForwardVector() * mCameraSpringArm->TargetArmLength;
}
FVector UPlayerCameraFunction::GetMuzzleRot()
{
	return mCamera->GetForwardVector();
}
void UPlayerCameraFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FHitResult> hitInfo = GetHitResultLookCrosshair();
	if(hitInfo.Num() > 0)
	{
		// ���ʰ��� ������
		for (FHitResult result : hitInfo)
		{
			// �������� ����ȴٸ�
			if (AItem* firstResultItem = Cast<AItem>(result.GetActor()))
			{
				mMainGameInstance->UIMng->GetItemText()->Enabled(firstResultItem);
				return;
			}
		}
	}
	mMainGameInstance->UIMng->GetItemText()->Disabled();
}

void UPlayerCameraFunction::CameraMoveSide(float axis)
{
	mTargetCharacter->AddControllerYawInput(axis * TMouseAxis * GetWorld()->GetDeltaSeconds());
}

void UPlayerCameraFunction::CameraMoveUp(float axis)
{
	mTargetCharacter->AddControllerPitchInput(axis * TMouseAxis * GetWorld()->GetDeltaSeconds());
}

void UPlayerCameraFunction::CameraLook(float rate)
{
	mCameraSpringArm->TargetArmLength = FMath::Clamp<float>(mCameraSpringArm->TargetArmLength + 4000 * rate * GetWorld()->GetDeltaSeconds(), 200.f, 700.f);
}