// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundMng.generated.h"


static const char* EventSounds[] = { "GraduallyHigh" , "GraduallyLow", "Appear", "SurpriseLow", "SurpriseMidium", "SurpriseHigh", "Bat" };

UENUM()
enum class EEventSound : uint8
{
	GraduallyHigh,
	GraduallyLow,
	Appear,
	SurpriseLow,
	SurpriseMidium,
	SurpriseHigh,
	Bat,

	Max
};

UCLASS()
class PROJECT_CUBE_API USoundMng : public UObject
{
	GENERATED_BODY()

public:
	USoundMng();
	USoundMng* Init();
	void PlayEventSound(const UObject* WorldContextObject, const EEventSound soundType);

private:
	TMap<EEventSound, class USoundCue*>  mEventSoundMap;
};
