// Fill out your copyright notice in the Description page of Project Settings.


#include "LightObject.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"

ALightObject::ALightObject()
{
	UBoxComponent* boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision = boxCollision;
	mCollision->SetupAttachment(GetRootComponent());

	mPointLight = CreateDefaultSubobject< UPointLightComponent>(TEXT("Point Light"));
	mPointLight->SetupAttachment(GetRootComponent());
}

void ALightObject::BeginPlay()
{
	Super::BeginPlay();

	if (mLightBuzzSound)
	{
		mAudioComponent->SetSound(mLightBuzzSound);
		mAudioComponent->Play();
	}

	if (mFlickerType == EFlickerType::EFT_Constants)
	{
		if (mConstantArray.Num() == 0)
			mFlickerType = EFlickerType::EFT_None;
		else
			mCurrConstant = 0;
	}

	mFlickerCurrIntencity = mPointLight->Intensity;
	if (!mbIsFlickerOverlapOnly && mFlickerType != EFlickerType::EFT_None)
	{
		switch (mFlickerType)
		{
		case EFlickerType::EFT_Default:
			ActivateFlickerConstantLerp();
			break;
		case EFlickerType::EFT_Constants:
			ActivateFlickerConstants();
			break;
		case EFlickerType::EFT_Random:
			ActivateFlickerRandomLerp();
			break;
		case EFlickerType::EFT_None:
		default:
			;
		}
	}
}

void ALightObject::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (FlickerBindAction.IsBound())
	{
		mFlickerElapsedTime += deltaTime;
		mPointLight->SetIntensity(FlickerBindAction.Execute());
	}
	if (mLightBuzzSound)
		if(mPointLight)
			mAudioComponent->SetVolumeMultiplier(mPointLight->Intensity*0.001f);
}

void ALightObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ALightObject::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;

	if (mbUseBrokenOverlap && mbBrokenOverlapEnter)
	{
		Broken();
		return;
	}
	if (mFlickerType != EFlickerType::EFT_None && mbIsFlickerOverlapOnly)
	{
		if (mbFlickerOverlapEnter)
		{
			if (!mbIsFlickerOverlapOnly)
			{
				switch (mFlickerType)
				{
				case EFlickerType::EFT_Default:
					ActivateFlickerConstantLerp();
					break;
				case EFlickerType::EFT_Constants:
					ActivateFlickerConstants();
					break;
				case EFlickerType::EFT_Random:
					ActivateFlickerRandomLerp();
					break;
				case EFlickerType::EFT_None:
				default:
					;
				}
			}
		}
	}
}

void ALightObject::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;
	if (mbUseBrokenOverlap && !mbBrokenOverlapEnter)
	{
		Broken();
		return;
	}
	if (mFlickerType != EFlickerType::EFT_None && mbIsFlickerOverlapOnly)
	{
		if (!mbFlickerOverlapEnter)
		{
			switch (mFlickerType)
			{
			case EFlickerType::EFT_Default:
				ActivateFlickerConstantLerp();
				break;
			case EFlickerType::EFT_Constants:
				ActivateFlickerConstants();
				break;
			case EFlickerType::EFT_Random:
				ActivateFlickerRandomLerp();
				break;
			case EFlickerType::EFT_None:
			default:
				;
			}
		}
	}
}

void ALightObject::ActivateFlickerConstantLerp()
{
	mbIsFlickerOverlapOnly = false;

	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();

	mFlickerElapsedTime = 0;
	mFlickerCurrIntencity = mPointLight->Intensity;

	FlickerBindAction.BindUObject(this, &ALightObject::GetConstantIntencity);
}
float ALightObject::GetConstantIntencity() 
{
	if (mFlickerTargetTime <= mFlickerElapsedTime) 
		mFlickerElapsedTime = 0;

	return FMath::Lerp(mFlickerCurrIntencity, mFlickerTargetIntencity, (mFlickerElapsedTime - mFlickerTargetTime) / mFlickerTargetTime);
};
void ALightObject::ActivateFlickerConstants()
{
	mbIsFlickerOverlapOnly = false;

	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();

	mFlickerElapsedTime = 0;
	mFlickerCurrIntencity = mPointLight->Intensity;

	FlickerBindAction.BindUObject(this, &ALightObject::GetConstantsIntencity);
}
float ALightObject::GetConstantsIntencity()
{
	if (mConstantArray[mCurrConstant] <= mFlickerElapsedTime) 
	{
		mFlickerElapsedTime = 0;
		mConstantArray.Num() - 1 <= mCurrConstant ? mCurrConstant = 0 : mCurrConstant += 1;
	}
	return FMath::Lerp(mFlickerCurrIntencity, mFlickerTargetIntencity, (mFlickerElapsedTime / mConstantArray[mCurrConstant]));
};
void ALightObject::ActivateFlickerRandomLerp()
{
	mbIsFlickerOverlapOnly = false;

	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();

	mFlickerElapsedTime = 0;
	mFlickerTargetIntencity = mFlickerTargetIntencity;
	mFlickerCurrIntencity = mPointLight->Intensity;
	mFlickerTargetTime = FMath::RandRange(mRandCycleMinTime, mRandCycleMaxTime);

	FlickerBindAction.BindUObject(this, &ALightObject::GeRandomIntencity);
}
float ALightObject::GeRandomIntencity() 
{
	if (mFlickerTargetTime < mFlickerElapsedTime)
	{
		mFlickerElapsedTime = 0;
		mFlickerTargetTime = FMath::RandRange(mRandCycleMinTime, mRandCycleMaxTime);
	}
	return FMath::Lerp(mFlickerCurrIntencity, mFlickerTargetIntencity, mFlickerElapsedTime / mFlickerTargetTime);
};
void ALightObject::DeativateFlickerLight()
{
	mFlickerType = EFlickerType::EFT_None;
	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();
}
void ALightObject::SwitchOn()
{
	mPointLight->SetIntensity(mSwitchIntencity);
}
void ALightObject::SwitchOff()
{
	mPointLight->SetIntensity(0);
}
void ALightObject::Broken()
{
	if (mBrokenSound)
		mAudioComponent->SetSound(mBrokenSound);
	
	mbUseBrokenOverlap = false;
	DeativateFlickerLight();
	mPointLight->DestroyComponent();
	if (mBrokenSound)
	{
		mAudioComponent->SetVolumeMultiplier(1);
		mAudioComponent->SetSound(mBrokenSound);
	}
}