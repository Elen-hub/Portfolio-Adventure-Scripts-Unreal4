// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundMng.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

USoundMng::USoundMng()
{
	// 사운드 디렉토리
	FString soundDirecotry("SoundWave'/Game/Sounds/EffectSound/");
	for (int i = 1; i < (uint8)EEventSound::Max; ++i)
	{
		if (!mSFXMap.Contains((EEventSound)i))
		{
			FString soundPath = soundDirecotry + "Event/" + EventSounds[i] + "_Cue." + EventSounds[i] + "_Cue'";
			ConstructorHelpers::FObjectFinder<USoundCue> sound(*soundPath);
			mSFXMap.Add((EEventSound)i, sound.Object);
		}
	}
	FString bgmDirecotry("SoundCue'/Game/Sounds/Music/");
	for (int i = 1; i < (uint8)EBGM::Max; ++i)
	{
		if (!mBGMMap.Contains((EBGM)i))
		{
			FString soundPath = bgmDirecotry + BGM[i] + "_Cue." + BGM[i] + "_Cue'";
			ConstructorHelpers::FObjectFinder<USoundCue> sound = ConstructorHelpers::FObjectFinder<USoundCue>(*soundPath);
			mBGMMap.Add((EBGM)i, sound.Object);
		}
	}

	mSFXVolume = 1.f;
	mBGMVolume = 0.5f;
}

USoundMng* USoundMng::Init()
{
	return this;
}

void USoundMng::PlayEventSound(const UObject* WorldContextObject, const EEventSound soundType)
{
	UGameplayStatics::PlaySound2D(WorldContextObject, mSFXMap[soundType], mSFXVolume);
}

void USoundMng::PlayBGM(const UObject* WorldContextObject, const EBGM soundType)
{
	if (mCurrBGM == soundType)
		return;

	if (mAudioComponent)
	{
		mAudioComponent->Stop();
		mAudioComponent->DestroyComponent();
		mAudioComponent = nullptr;
	}
	mCurrBGM = soundType;
	mAudioComponent = UGameplayStatics::SpawnSound2D(WorldContextObject, mBGMMap[soundType], mBGMVolume);
	mAudioComponent->Play();
}
