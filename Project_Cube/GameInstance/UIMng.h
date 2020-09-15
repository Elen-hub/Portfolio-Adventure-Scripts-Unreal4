// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIMng.generated.h"

/**
 * 
 */

static const char* EUITypeString[] = { "MainUI" , "ItemText"};

UENUM()
enum class EUIType : uint8
{
	MainUI,
	ItemText,
	Max
};
UCLASS()
class PROJECT_CUBE_API UUIMng : public UObject
{
	GENERATED_BODY()
	
public:
	UUIMng();
private:
	TMap<EUIType, UClass*>  mWidgetClassMap;
	TMap<EUIType, class UBaseWidget*> mUIMap;
	class UMainUI_ItemText* mItemText;
	class UGameInstance* mGameInstance;

private:
	template <class T = UBaseWidget> T* InstanceBaseWidget(const EUIType uiType);
	template <class T = UUserWidget> T* InstanceWidget(const EUIType uiType);
	UBaseWidget* Open(const EUIType uiName);
public:
	UUIMng* Init(class UMainGameInstance* gameInstance);
	UMainUI_ItemText* GetItemText();
	template <class T = UBaseWidget> T* Open(const EUIType uiType);
	template <class T = UBaseWidget> T* Get(const EUIType uiType);
	void Close(EUIType uiName);
};

template<class T>
T* UUIMng::InstanceBaseWidget(const EUIType uiType)
{
	// 참조된 클래스로 오브젝트 인스턴싱
	T* instanceWidget = CreateWidget<T>(mGameInstance->GetWorld(), mWidgetClassMap[uiType]);
	mUIMap.Add(uiType, instanceWidget);
	mUIMap[uiType]->AddToViewport();
	return mUIMap[uiType]->Init();
}
template<class T>
T* UUIMng::InstanceWidget(const EUIType uiType)
{
	// UBaseWidget이 파생되지 않기때문에 컨테이너에 저장하지않고 리턴
	T* instanceWidget = CreateWidget<T>(mGameInstance->GetWorld(), mWidgetClassMap[uiType]);
	instanceWidget->AddToViewport();
	return instanceWidget;
}

template<class T>
T* UUIMng::Open(const EUIType uiType)
{
	return Cast<T>(Open(uiType));
}
template<class T>
T* UUIMng::Get(const EUIType uiType)
{
	if (!mUIMap.Contains(uiType))
		InstanceBaseWidget(uiType);

	return Cast<T>(mUIMap[uiType]);
}