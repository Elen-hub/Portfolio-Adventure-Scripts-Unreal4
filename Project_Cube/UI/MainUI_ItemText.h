// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI_ItemText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMainUI_ItemText : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class AItem* mItem;
	UPROPERTY()
	class UTextBlock* mNameText;
	FVector mAddPos;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void Enabled(AItem* item);
	void Disabled();
};
