// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI_ItemText.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Project_Cube/Object/Item.h"

void UMainUI_ItemText::NativeConstruct()
{
	Super::NativeConstruct();

	// SetAlignmentInViewport(FVector2D(0.f));
	mNameText = WidgetTree->FindWidget<UTextBlock>(TEXT("ItemText"));
	SetVisibility(ESlateVisibility::Hidden);
	mAddPos = FVector(0.f);
}
void UMainUI_ItemText::Enabled(AItem* item)
{
	if (item == nullptr)
	{
		Disabled();
		return;
	}

	if (mItem == item)
		return;

	mItem = item;
	mNameText->SetText(item->GetItemSelectText());

	FVector2D screenLocation;
	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(mItem->GetActorLocation(), screenLocation);
	SetPositionInViewport(screenLocation);
	SetVisibility(ESlateVisibility::Visible);
}
void UMainUI_ItemText::Disabled()
{
	SetVisibility(ESlateVisibility::Hidden);
	mItem = nullptr;
}
void UMainUI_ItemText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// mItem 이 있다면 텍스트 위치조정
	if (mItem)
	{
		FVector2D screenLocation;
		GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(mItem->GetActorLocation(), screenLocation);
		SetPositionInViewport(screenLocation);
	}
}