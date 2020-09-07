// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI_WeaponStatus.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Project_Cube/Character/BaseHero.h"
#include "Project_Cube/Object/BaseWeapon.h"

void UMainUI_WeaponStatus::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = WidgetTree->FindWidget<UTextBlock>(TEXT("Name"));
	mCurrMagazine = WidgetTree->FindWidget<UTextBlock>(TEXT("CurrMagazine"));
	mMaxMagazine = WidgetTree->FindWidget<UTextBlock>(TEXT("MaxMagazine"));
}

void UMainUI_WeaponStatus::Tick(float deltaTime)
{
	if (mWeapon == nullptr || mWeapon != mBaseHero->GetWeapon())
	{
		mWeapon = mBaseHero->GetWeapon();
		if (mWeapon)
		{
			SetVisibility(ESlateVisibility::Visible);
			mNameText->SetText(FText::FromString(mWeapon->Name));
		}
		else
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
		return;
	}

	const float currMagazine = mWeapon->CurrMagazine;
	const float maxMagazine = mWeapon->MaxMagazine;
	const float magazinePer = currMagazine / maxMagazine;
	mCurrMagazine->SetText(FText::FromString(FString::FromInt(currMagazine)));
	if (magazinePer >= 0.5f)
	{
		mCurrMagazine->SetColorAndOpacity(mDefaultMagazineColor);
	}
	else if (magazinePer > 0.15f)
	{
		mCurrMagazine->SetColorAndOpacity(mLackMagazineColor);
	}
	else
	{
		mCurrMagazine->SetColorAndOpacity(mEmptyMagazineColor);
	}
}

void UMainUI_WeaponStatus::Enabled(ABaseHero* hero)
{
	mBaseHero = hero;
}

void UMainUI_WeaponStatus::Disabled()
{

}
