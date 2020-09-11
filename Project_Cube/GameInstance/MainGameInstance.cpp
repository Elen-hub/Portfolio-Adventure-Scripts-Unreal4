// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Cube/User.h"
#include "MainGameInstance.h"
#include "CharacterMng.h"
#include "UIMng.h"
#include "SpawnMng.h"
#include "SoundMng.h"


void UMainGameInstance::Init()
{
	Super::Init();

	CharacterMng = NewObject<UCharacterMng>()->Init();
	UIMng = NewObject<UUIMng>()->Init(this);
	SpawnMng = NewObject<USpawnMng>()->Init(this);
	SoundMng = NewObject<USoundMng>()->Init();

	Main = this;
}