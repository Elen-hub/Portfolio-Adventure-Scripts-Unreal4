// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_Cube/User.h"
#include "MainUI_CharacterStatus.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Project_Cube/Character/BaseHero.h"
#include "Project_Cube/Character/SprintFunction.h"
#include "Project_Cube/Character/StatFunction.h"

void UMainUI_CharacterStatus::NativeConstruct()
{
	Super::NativeConstruct();

	mProgressHP = WidgetTree->FindWidget<UProgressBar>(TEXT("ProgressHP"));
	mProgressMP = WidgetTree->FindWidget<UProgressBar>(TEXT("ProgressMP"));
	mProgressSP = WidgetTree->FindWidget<UProgressBar>(TEXT("ProgressSP"));
}
void UMainUI_CharacterStatus::Enabled(ABaseHero* baseHero)
{
	mBaseHero = baseHero;
}

void UMainUI_CharacterStatus::Disabled()
{
	mBaseHero = nullptr;
}

void UMainUI_CharacterStatus::Tick(float deltaTime)
{
	// HP Option (Lerp)
	const float hpPercent = PERCENT(mBaseHero->StatFunction()->CurrHP(), mBaseHero->StatFunction()->GetStat()->HP);
	const float nextPercent = mProgressHP->Percent + (hpPercent - mProgressHP->Percent) * deltaTime * 1.5f;
	if (FMath::Abs(nextPercent - hpPercent) > 0.001f)
	{
		mProgressHP->SetPercent(nextPercent);
	}
	else
	{
		mProgressHP->SetPercent(hpPercent);
	}

	mProgressHP->SetPercent(mProgressHP->Percent + (hpPercent- mProgressHP->Percent) * deltaTime*1.5f);

	// Stamina Option
	mProgressSP->SetPercent(mBaseHero->SprintFunction()->GetStaminaPercent());
	switch (mBaseHero->SprintFunction()->GetSprintState())
	{
	case ESprintState::ESS_Default:
		mProgressSP->SetFillColorAndOpacity(mStaminaDefaultColor);
		break;
	case ESprintState::ESS_Exhausted:
		mProgressSP->SetFillColorAndOpacity(mStaminaExhaustedColor);
		break;
	case ESprintState::ESS_Fatal:
		mProgressSP->SetFillColorAndOpacity(mStaminaFatalColor);
		break;
	default:
		break;
	}
}
