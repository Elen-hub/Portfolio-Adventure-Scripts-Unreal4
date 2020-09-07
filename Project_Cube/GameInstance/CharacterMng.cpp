// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMng.h"
#include "Engine/World.h"
#include "Project_Cube/Character/BaseCharacter.h"

UCharacterMng* UCharacterMng::Init()
{
	return this;
}

ABaseCharacter* UCharacterMng::SpawnEnermy(ABaseCharacter* spawnActor, FVector worldLocation, FRotator localRotation)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Template = spawnActor;
	ABaseCharacter* spawnCharacter = spawnActor->GetWorld()->SpawnActor<ABaseCharacter>(spawnActor->GetClass(), worldLocation, localRotation, spawnParams);
	return spawnCharacter;
}