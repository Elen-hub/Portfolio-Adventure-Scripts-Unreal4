// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI_CharacterStatus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMainUI_CharacterStatus : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UProgressBar* mProgressHP;
	UPROPERTY()
	UProgressBar* mProgressMP;
	UPROPERTY()
	UProgressBar* mProgressSP;
private:
	class ABaseHero* mBaseHero;

	const FLinearColor mStaminaDefaultColor = FLinearColor(1.f, 1.f, 0.f, 1.f);
	const FLinearColor mStaminaExhaustedColor = FLinearColor(0.1f, 0.1f, 0.f, 1.f);
	const FLinearColor mStaminaFatalColor = FLinearColor(0.1f, 0.f, 0.f, 1.f);

protected:
	virtual void NativeConstruct() override;
public:
	void Enabled(ABaseHero* baseHero);
	void Disabled();
	void Tick(float deltaTime);
};
