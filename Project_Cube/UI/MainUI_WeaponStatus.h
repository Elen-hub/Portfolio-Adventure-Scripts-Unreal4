// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI_WeaponStatus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMainUI_WeaponStatus : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class ABaseHero* mBaseHero;
	class ABaseWeapon* mWeapon;

	UPROPERTY()
	class UTextBlock* mNameText;
	UPROPERTY()
	class UTextBlock* mCurrMagazine;
	UPROPERTY()
	class UTextBlock* mMaxMagazine;
protected:
	virtual void NativeConstruct() override;

public:	
	void Tick(float deltaTime);
	void Enabled(ABaseHero* hero);
	void Disabled();
};
