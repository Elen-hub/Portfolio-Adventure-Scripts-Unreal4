// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	class ABaseHero* MainCharacter;
	UPROPERTY()
	class UCharacterMng* CharacterMng;
	UPROPERTY()
	class UUIMng* UIMng;
	UPROPERTY()
	class USpawnMng* SpawnMng;

	virtual void Init() override;
};
