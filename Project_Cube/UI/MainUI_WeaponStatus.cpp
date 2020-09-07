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
		mNameText->SetText(FText::FromString(mWeapon->Name));
		return;
	}

	mCurrMagazine->SetText(FText::FromString(FString::FromInt(mWeapon->CurrMagazine)));
}

void UMainUI_WeaponStatus::Enabled(ABaseHero* hero)
{
	mBaseHero = hero;
}

void UMainUI_WeaponStatus::Disabled()
{

}
