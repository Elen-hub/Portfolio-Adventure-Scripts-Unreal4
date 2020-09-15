// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_Cube/UI/BaseWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMainUI : public UBaseWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UMainUI_CharacterStatus* mCharacterStatus;
	UPROPERTY()
	class UMainUI_WeaponStatus* mWeaponStatus;
	UPROPERTY()
	class UMainUI_Crosshair* mCrosshair;
	UPROPERTY()
	class UImage* mShowImage;
	UPROPERTY()
	class ABaseHero* mBaseHero;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void Enabled(ABaseHero* baseHero);
	void Disabled();
	void ActivateTexture(bool isActivate);
	void SetTexture(class UTexture2D* image);
	virtual UBaseWidget* Init() override;
};
