// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundMng.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

USoundMng* USoundMng::Init()
{
	return this;
}

void USoundMng::PlayEffectSound(const UObject* WorldContextObject, USoundCue* sound)
{
	UGameplayStatics::PlaySound2D(WorldContextObject, sound);
}

void USoundMng::StopEffectSound(class USoundCue* sound)
{
	UGameplayStatics::PrimeSound(sound);
}