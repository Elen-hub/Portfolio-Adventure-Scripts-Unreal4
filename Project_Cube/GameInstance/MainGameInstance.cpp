// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Cube/User.h"
#include "MainGameInstance.h"

#include "Project_Cube/UI/MainUI.h"


void UMainGameInstance::Init()
{
	Super::Init();
	Main = this;
}

void UMainGameInstance::SetMainCharacter(ABaseHero* mainCharacter) 
{
	mMainCharacter = mainCharacter;

	CharacterMng = NewObject<UCharacterMng>()->Init();
	UIMng = NewObject<UUIMng>()->Init(this);
	SpawnMng = NewObject<USpawnMng>()->Init(this);
	SoundMng = NewObject<USoundMng>()->Init();
	MapMng = NewObject<UMapMng>()->Init();

	UIMng->Open<UMainUI>(EUIType::MainUI)->Enabled(mainCharacter);
}