// Fill out your copyright notice in the Description page of Project Settings.


#include "MapMng.h"
#include "Project_Cube/Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

UMapMng::UMapMng()
{

}

UMapMng* UMapMng::Init()
{
	return this;
}

void UMapMng::ChangeLevel(ABaseCharacter* mainCharacter, const ELevel level)
{
	UGameplayStatics::OpenLevel(mainCharacter->GetWorld(), Levels[(uint8)level]);
}
