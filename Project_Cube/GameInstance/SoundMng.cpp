// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundMng.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Project_Cube/User.h"

USoundMng::USoundMng()
{
	// 사운드 디렉토리
	FString uiDirecotry("SoundWave'/Game/Sounds/EffectSound/");
	for (int i = 0; i < (uint8)EEventSound::Max; ++i)
	{
		if (!mEventSoundMap.Contains((EEventSound)i))
		{
			FString soundPath = uiDirecotry + "Event/" + EventSounds[i] + "_Cue." + EventSounds[i] + "_Cue'";
			static ConstructorHelpers::FObjectFinder<USoundCue> sound(*soundPath);
			mEventSoundMap.Add((EEventSound)i, sound.Object);
		}
	}
}

USoundMng* USoundMng::Init()
{

	return this;
}

void USoundMng::PlayEventSound(const UObject* WorldContextObject, const EEventSound soundType)
{
	UGameplayStatics::PlaySound2D(WorldContextObject, mEventSoundMap[soundType]);
}