// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat.generated.h"

USTRUCT()
struct FCharacterInformation
{
	GENERATED_USTRUCT_BODY()

	uint8 Handle;

	FName AssetPath;
	FName IconPath;

	FText Name;
	FText Explanation;
};

USTRUCT()
struct FCombatStat
{
	GENERATED_USTRUCT_BODY()

	float HP;
	float SP;

};