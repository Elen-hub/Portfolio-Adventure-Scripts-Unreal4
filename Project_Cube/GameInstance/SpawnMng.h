// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpawnMng.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API USpawnMng : public UObject
{
	GENERATED_BODY()
	
public:
	USpawnMng();
public:
	USpawnMng* Init();
};
