// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterMng.generated.h"

USTRUCT()
struct FCharacterArr
{
	GENERATED_USTRUCT_BODY()

	FCharacterArr(){ }

	TArray<class BaseCharacter*> CharacterArr;
};

UCLASS()
class PROJECT_CUBE_API UCharacterMng : public UObject
{
	GENERATED_BODY()

private:
	TMap<int, FCharacterArr> mCharacterList;
	TMap<int, FCharacterArr> mCharacterPool;
public:
	UCharacterMng* Init();
	class ABaseCharacter* SpawnEnermy(ABaseCharacter* spawnActor, FVector worldLocation, FRotator localRotation);
};
