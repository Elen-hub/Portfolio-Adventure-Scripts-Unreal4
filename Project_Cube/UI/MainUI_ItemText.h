// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI_ItemText.generated.h"

/**
 * 
 */
UENUM()
enum class EItemTextType : uint8
{
	Item,
	Interaction
};

UCLASS()
class PROJECT_CUBE_API UMainUI_ItemText : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class AActor* mItem;
	UPROPERTY()
	class UTextBlock* mNameText;
	UPROPERTY()
	class UTextBlock* mKeyText;
	FVector mAddPos;
	TMap<EItemTextType, FText> mSelectKeyMap;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void Enabled(AActor* item, FText text, const EItemTextType type);
	void Disabled();
};
