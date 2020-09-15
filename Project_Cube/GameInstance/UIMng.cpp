// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMng.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Project_Cube/UI/BaseWidget.h"
#include "Project_Cube/UI/MainUI_ItemText.h"

#include "MainGameInstance.h"
#include "Project_Cube/UI/MainUI.h"

UUIMng::UUIMng()
{
	// UI ���丮
	FString uiDirecotry("WidgetBlueprint'/Game/UI/");
	for (int i = 0; i < (uint8)EUIType::Max; ++i)
	{
		// Ŭ���� ����, ����
		if (!mWidgetClassMap.Contains((EUIType)i))
		{
			FString uiPath = uiDirecotry + EUITypeString[i] + "_BP." + EUITypeString[i] + "_BP_C";
			FStringClassReference widgetClassRef(uiPath);
			if (UClass* ui = widgetClassRef.TryLoadClass<UUserWidget>())
				mWidgetClassMap.Add((EUIType)i, ui);
		}
	}
}
UUIMng* UUIMng::Init(UMainGameInstance* gameInstance)
{
	mGameInstance = gameInstance;

	Open<UMainUI>(EUIType::MainUI)->Enabled(gameInstance->MainCharacter);
	return this;
}
UBaseWidget* UUIMng::Open(const EUIType uiType)
{
	if (!mUIMap.Contains(uiType))
		InstanceBaseWidget(uiType);

	SetVisibility(ESlateVisibility::Visible);
	mUIMap[uiType]->Open();
	return mUIMap[uiType];
}
void UUIMng::Close(EUIType uiType)
{
	mUIMap[uiType]->Close();
}

UMainUI_ItemText* UUIMng::GetItemText()
{
	if (!mItemText)
		mItemText = InstanceWidget<UMainUI_ItemText>(EUIType::ItemText);

	return mItemText;
}