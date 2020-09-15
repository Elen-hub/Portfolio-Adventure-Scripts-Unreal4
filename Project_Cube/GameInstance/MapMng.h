// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapMng.generated.h"

/**
 * 
 */

static const char* Levels[] = { "Level_Hospital", "Level_Station" };
UENUM()
enum class ELevel : uint8
{
	Level_Hospital,
	Level_Station,
};
UCLASS()
class PROJECT_CUBE_API UMapMng : public UObject
{
	GENERATED_BODY()
	

public:
	UMapMng();
	UMapMng* Init();
	void ChangeLevel(class ABaseCharacter* mainCharacter, const ELevel level);
};
