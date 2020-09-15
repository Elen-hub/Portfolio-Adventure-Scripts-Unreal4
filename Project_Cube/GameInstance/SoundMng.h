// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundMng.generated.h"


static const char* EventSounds[] = { "Blank", "GraduallyHigh" , "GraduallyLow", "Appear", "SurpriseLow", "SurpriseMidium", "SurpriseVeryHigh", "Bat" };
static const char* BGM[] = { "Blank", "Main", "Mistery","Ghostly_Villa", "Frozen" };

UENUM()
enum class EEventSound : uint8
{
	None,

	GraduallyHigh,
	GraduallyLow,
	Appear,
	SurpriseLow,
	SurpriseMidium,
	SurpriseHigh,
	Bat,

	Max
};
UENUM()
enum class EBGM : uint8
{
	None,

	Main,
	Mistery,
	Ghostly_Villa,
	Frozen,

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
	void PlayBGM(const UObject* WorldContextObject, const EBGM soundType);
	FORCEINLINE float GetBGMVolume() { return mBGMVolume; }
	FORCEINLINE float GetSFXVolume() { return mSFXVolume; }
	void SetBGMVolume(float volume) { mBGMVolume = volume; }
	void SetSFXVolume(float volume) { mSFXVolume = volume; }
protected:
	EBGM mCurrBGM;
private:
	TMap<EEventSound, class USoundCue*>  mSFXMap;
	TMap<EBGM, class USoundCue*>  mBGMMap;
	class UAudioComponent* mAudioComponent;
	float mBGMVolume;
	float mSFXVolume;
};
