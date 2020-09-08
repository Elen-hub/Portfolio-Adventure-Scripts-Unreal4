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
	const FLinearColor mDefaultMagazineColor = FLinearColor(1.f, 1.f, 1.f, 0.5f);
	const FLinearColor mLackMagazineColor = FLinearColor(1.f, 0.1f, 0.f, 0.5f);
	const FLinearColor mEmptyMagazineColor = FLinearColor(1.f, 0.f, 0.f, 0.5f);

	class ABaseHero* mBaseHero;
	class ABaseWeapon* mWeapon;

	UPROPERTY()
	class UTextBlock* mNameText;
	UPROPERTY()
	class UTextBlock* mCurrMagazine;
	UPROPERTY()
	class UTextBlock* mMaxMagazine;
	UPROPERTY()
	class UTextBlock* mWeaponStatus;
protected:
	virtual void NativeConstruct() override;

public:	
	void Tick(float deltaTime);
	void Enabled(ABaseHero* hero);
	void Disabled();
};
