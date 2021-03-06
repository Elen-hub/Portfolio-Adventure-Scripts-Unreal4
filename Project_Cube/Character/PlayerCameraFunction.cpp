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
#include "Project_Cube/Object/InteractionObject.h"

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

void UPlayerCameraFunction::Set(ABaseCharacter* character)
{
	mTargetCharacter = character;
}

void UPlayerCameraFunction::SetRebound(const float pitch, const float yaw)
{
	mTargetCharacter->AddControllerPitchInput(pitch * GetWorld()->GetDeltaSeconds());
	mTargetCharacter->AddControllerYawInput(yaw* GetWorld()->GetDeltaSeconds());
}

// 크로스헤어에서 보이는 충돌오브젝트를 모두 얻는함수
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

// 크로스헤어에서 보이는 첫번째 아이템을 얻는 함수
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
			{
				if(!item->IsEquip())
					return item;
			}
		}
	}
	return nullptr;
}
AInteractionObject* UPlayerCameraFunction::GetInteractionLookCrosshair()
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
			if (AInteractionObject* firstResultObject = Cast<AInteractionObject>(result.GetActor()))
				return firstResultObject;
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
		// 최초검출 아이템
		for (FHitResult result : hitInfo)
		{
			// 아이템이 검출된다면
			if (AItem* firstResultItem = Cast<AItem>(result.GetActor()))
			{
				if (!firstResultItem->IsEquip())
				{
					mbUsingUI = true;
					Main->UIMng->GetItemText()->Enabled(firstResultItem, firstResultItem->GetItemSelectText(), EItemTextType::Item);
					return;
				}
			}
			if (AInteractionObject* firstResultObject = Cast<AInteractionObject>(result.GetActor()))
			{
				mbUsingUI = true;
				Main->UIMng->GetItemText()->Enabled(firstResultObject, firstResultObject->GetInteractionExplanation(), EItemTextType::Interaction);
				return;
			}
		}
	}
	if(mbUsingUI)
		Main->UIMng->GetItemText()->Disabled();
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