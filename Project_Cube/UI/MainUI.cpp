// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "Project_Cube/Character/BaseCharacter.h"
#include "Project_Cube/GameInstance/MainGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "MainUI_CharacterStatus.h"
#include "MainUI_Crosshair.h"
#include "MainUI_ItemText.h"
#include "MainUI_WeaponStatus.h"
#include "Components/Image.h"


void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	mCharacterStatus = WidgetTree->FindWidget<UMainUI_CharacterStatus>(TEXT("MainUI_CharacterStatus_BP"));
	mWeaponStatus = WidgetTree->FindWidget<UMainUI_WeaponStatus>(TEXT("MainUI_WeaponStatus_BP"));
	mCrosshair = WidgetTree->FindWidget<UMainUI_Crosshair>(TEXT("MainUI_Crosshair_BP"));

	mShowImage = WidgetTree->FindWidget<UImage>(TEXT("ShowTexture"));
}
UBaseWidget* UMainUI::Init()
{
	Super::Init();
	mShowImage->SetVisibility(ESlateVisibility::Hidden);
	return this;
}
void UMainUI::Enabled(ABaseHero* baseHero)
{
	mCharacterStatus->Enabled(baseHero);
	mWeaponStatus->Enabled(baseHero);
	mCrosshair->Enabled(baseHero);
	mBaseHero = baseHero;
}
void UMainUI::Disabled()
{
	mCharacterStatus->Disabled();
	mWeaponStatus->Disabled();
	mCrosshair->Disabled();
	mBaseHero = nullptr;
}
void UMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 메인캐릭터가 존재할경우에만 프레임함수 작동
	if (!mBaseHero)
		return;

	// 하위위젯 프레임함수 호출
	mCharacterStatus->Tick(InDeltaTime);
	mWeaponStatus->Tick(InDeltaTime);
	mCrosshair->Tick(InDeltaTime);
}

void UMainUI::ActivateTexture(bool isActivate)
{
	if (isActivate)
	{
		mShowImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mShowImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainUI::SetTexture(UTexture2D* texture)
{
	mShowImage->SetBrushFromTexture(texture);
}
