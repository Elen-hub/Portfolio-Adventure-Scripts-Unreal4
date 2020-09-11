// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundMng.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API USoundMng : public UObject
{
	GENERATED_BODY()

public:
	USoundMng* Init();
	static void PlayEffectSound(const UObject* WorldContextObject, class USoundCue* sound);
	static void StopEffectSound(USoundCue* sound);
};
