// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI_Crosshair.h"
#include "Blueprint/WidgetTree.h"
#include "Project_Cube/Character/BaseHero.h"
#include "Components/Image.h"

void UMainUI_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();
	mCrosshairImg = WidgetTree->FindWidget<UImage>(TEXT("Crosshair"));
}

void UMainUI_Crosshair::Enabled(ABaseHero* baseHero)
{
	mBaseHero = baseHero;
}
void UMainUI_Crosshair::Disabled()
{
	mBaseHero = nullptr;
}
void UMainUI_Crosshair::Tick(float deltaTime)
{
	// 반동범위
	mCrosshairImg->SetRenderScale(FVector2D(1 + mBaseHero->GetCurrRecoil() * 0.1f));
	UE_LOG(LogTemp, Warning, TEXT("%f"), 1 + mBaseHero->GetCurrRecoil() * 0.1f)
}
