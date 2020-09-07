// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
UBaseWidget* UBaseWidget::Init()
{
	return this;
}
void UBaseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
void UBaseWidget::Open()
{
	SetVisibility(ESlateVisibility::Visible);
}
void UBaseWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}