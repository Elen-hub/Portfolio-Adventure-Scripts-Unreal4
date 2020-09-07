// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI_Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMainUI_Crosshair : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class ABaseHero* mBaseHero;
	class UImage* mCrosshairImg;

protected:
	virtual void NativeConstruct() override;
public:
	void Enabled(ABaseHero* baseHero);
	void Disabled();
	void Tick(float deltaTime);
};
