// Fill out your copyright notice in the Description page of Project Settings.


#include "LightObject.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

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

	mFlickerCurrIntencity = mPointLight->Intensity;
	if (!mIsFlickerOverlapOnly && mFlickerType != EFlickerType::EFT_None)
	{
		switch (mFlickerType)
		{
		case EFlickerType::EFT_Default:
			ActivateFlickerConstantCycle();
			break;
		case EFlickerType::EFT_Sin:
			ActivateFlickerSinCycle();
			break;
		case EFlickerType::EFT_Random:
			ActivateFlickerRandomCycle();
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

	if (mFlickerType != EFlickerType::EFT_None && mIsFlickerOverlapOnly)
	{
		if (mIsOverlapEnter)
		{
			if (!mIsFlickerOverlapOnly)
			{
				switch (mFlickerType)
				{
				case EFlickerType::EFT_Default:
					ActivateFlickerConstantCycle();
					break;
				case EFlickerType::EFT_Sin:
					ActivateFlickerSinCycle();
					break;
				case EFlickerType::EFT_Random:
					ActivateFlickerRandomCycle();
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

	if (mFlickerType != EFlickerType::EFT_None && mIsFlickerOverlapOnly)
	{
		if (!mIsOverlapEnter)
		{
			switch (mFlickerType)
			{
			case EFlickerType::EFT_Default:
				ActivateFlickerConstantCycle();
				break;
			case EFlickerType::EFT_Sin:
				ActivateFlickerSinCycle();
				break;
			case EFlickerType::EFT_Random:
				ActivateFlickerRandomCycle();
				break;
			case EFlickerType::EFT_None:
			default:
				;
			}
		}
	}
}

void ALightObject::ActivateFlickerConstantCycle()
{
	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();

	mFlickerElapsedTime = 0;
	mFlickerCurrIntencity = mPointLight->Intensity;

	FlickerBindAction.BindUObject(this, &ALightObject::GetConstantCycleIntencity);
}

void ALightObject::ActivateFlickerSinCycle()
{
	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();

	mFlickerElapsedTime = 0;
	mFlickerCurrIntencity = mPointLight->Intensity;

	FlickerBindAction.BindUObject(this, &ALightObject::GetSinCycleIntencity);
}

void ALightObject::ActivateFlickerRandomCycle()
{
	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();

	mFlickerElapsedTime = 0;
	mFlickerTargetIntencity = mFlickerTargetIntencity;
	mFlickerCurrIntencity = mPointLight->Intensity;
	mFlickerTargetTime = FMath::RandRange(mRandCycleMinTime, mRandCycleMaxTime);

	FlickerBindAction.BindUObject(this, &ALightObject::GeRandomCycleIntencity);
}

void ALightObject::DeativateFlickerLight()
{
	if (FlickerBindAction.IsBound())
		FlickerBindAction.Unbind();
}
