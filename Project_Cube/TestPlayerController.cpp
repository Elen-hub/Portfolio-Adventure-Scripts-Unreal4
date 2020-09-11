// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

ATestPlayerController::ATestPlayerController()
{

}
void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// SetAudioListenerOverride(GetCharacter(), FVector(0, 0, 50.f), FRotator::ZeroRotator);
}