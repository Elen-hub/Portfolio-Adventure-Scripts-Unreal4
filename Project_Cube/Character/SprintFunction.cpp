// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Cube/User.h"
#include "SprintFunction.h"
#include "BaseHero.h"

// Sets default values for this component's properties
USprintFunction* USprintFunction::Init()
{
	PrimaryComponentTick.bCanEverTick = true;

	ABaseHero* hero = Cast<ABaseHero>(GetOwner());
	mMaxStamina = &hero->TMaxStamina;
	mRecoveryStamina = &hero->TRecoveryStamina;

	mbUseSprint = false;
	mSprintState = ESprintState::ESS_Default;
	mCurrStamina = 100.f;

	return this;
}

// Called every frame
void USprintFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 페이탈상태
	if (mSprintState == ESprintState::ESS_Fatal)
	{
		mbUseSprint = false;
		mCurrStamina += *mRecoveryStamina * DeltaTime;
		// 지침상태 채크
		if (mCurrStamina >= *mMaxStamina * mExhaustedStamina)
			mSprintState = ESprintState::ESS_Exhausted;
	}
	else
	{
		// 증감
		if (mbUseSprint)
		{
			mCurrStamina = FMath::Clamp<float>(mCurrStamina - 20.f * DeltaTime, 0, *mMaxStamina);
		}
		else
		{
			mCurrStamina = FMath::Clamp<float>(mCurrStamina + *mRecoveryStamina * DeltaTime, 0, *mMaxStamina);
			// 상태변경
			if (mCurrStamina < *mMaxStamina * mExhaustedStamina)
			{
				mSprintState = ESprintState::ESS_Exhausted;
				if (mCurrStamina <= 0)
				{
					mbUseSprint = false;
					mSprintState = ESprintState::ESS_Fatal;
				}
			}
			else
				mSprintState = ESprintState::ESS_Default;;
		}
	}
}

void USprintFunction::SprintActivate()
{
	if (mbPossibleSprint)
	{
		if (mSprintState != ESprintState::ESS_Fatal)
			mbUseSprint = true;
	}
}

void USprintFunction::SprintDeactivate()
{
	mbUseSprint = false;
}
