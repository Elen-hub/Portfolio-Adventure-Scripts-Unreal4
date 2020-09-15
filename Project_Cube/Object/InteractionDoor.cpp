// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionDoor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

AInteractionDoor::AInteractionDoor()
{
	mInteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collision"));
	mInteractionCollision->SetupAttachment(GetRootComponent());
	mInteractionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mInteractionCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mInteractionCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	mRotatorTime = 1.f;
}
void AInteractionDoor::BeginPlay()
{
	Super::BeginPlay();

	mRotatorElapsedTime = mRotatorTime;
}

void AInteractionDoor::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (mRotatorElapsedTime < mRotatorTime)
		mRotatorElapsedTime += deltaTime;

	if (mIsOpen)
	{
		SetActorRotation(FMath::Lerp(mCloseRot, mOpenRot, mRotatorElapsedTime / mRotatorTime));
	}
	else
	{
		SetActorRotation(FMath::Lerp(mOpenRot, mCloseRot, mRotatorElapsedTime / mRotatorTime));
	}
}

FText const AInteractionDoor::GetInteractionExplanation()
{
	FText returnText;

	if (mIsOpen)
	{
		returnText = FText::FromString("Close door");
	}
	else
	{
		if (mIsLocked)
			returnText = FText::FromString("[Locked] Use Key");
		else
			returnText = FText::FromString("Open the door");
	}

	return returnText;
}

void AInteractionDoor::Interaction()
{			
	// 열려있다면
	if (mIsOpen)		
	{

	}
	else
	{		
		// 닫혀있고 잠겨있다면
		if (mIsLocked)
		{
			// 만약 인벤토리에 키가 존재한다면
			// 테스트
			if (true)
			{
				// 잠금장치를 풀음
				mIsLocked = false;
				if (mIsBrokenKey)
				{
					// 인벤토리에서 열쇠 제거
				}
				if (mUseKeySound)
				{
					mAudioComponent->SetSound(mUseKeySound);
					mAudioComponent->Play();
				}
			}
			else
			{
				// 열 수 없음
				if (mOpenLockDoorSound)
				{
					mAudioComponent->SetSound(mOpenLockDoorSound);
					mAudioComponent->Play();
				}
			}
		}
		else
		{
			// 잠겨있지 않다면
			Open();
		}
	}
}

void AInteractionDoor::Open()
{
	mIsOpen = true;
	mRotatorElapsedTime = 0;
	if (mOpenSound)
	{
		mAudioComponent->SetSound(mOpenSound);
		mAudioComponent->Play();
	}
}

void AInteractionDoor::Close()
{
	mIsOpen = false;
	mRotatorElapsedTime = 0;
}