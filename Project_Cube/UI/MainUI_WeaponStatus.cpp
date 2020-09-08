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
	mWeaponStatus = WidgetTree->FindWidget<UTextBlock>(TEXT("Status"));

	UWidgetBlueprintGeneratedClass* widgetAni = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
	for (UWidgetAnimation* animation : widgetAni->Animations)
	{
		if (TEXT("FlickerText_INST") == animation->GetName())
		{
			PlayAnimation(animation, 0.f, 0);
			return;
		}
	}
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
	if (mBaseHero->IsReloading())
	{
		mWeaponStatus->SetText(FText::FromString("Reload"));
		mWeaponStatus->SetVisibility(ESlateVisibility::Visible);
	}
	else if (mBaseHero->GetWeapon()->CurrMagazine == 0) 
	{
		mWeaponStatus->SetText(FText::FromString("Empty"));
		mWeaponStatus->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mWeaponStatus->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainUI_WeaponStatus::Enabled(ABaseHero* hero)
{
	mBaseHero = hero;
}

void UMainUI_WeaponStatus::Disabled()
{

}
