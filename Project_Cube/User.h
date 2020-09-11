// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/GameInstance/MainGameInstance.h"
#include "Project_Cube/GameInstance/UIMng.h"
#include "Project_Cube/GameInstance/CharacterMng.h"
#include "Project_Cube/GameInstance/SpawnMng.h"
#include "Project_Cube/GameInstance/SoundMng.h"
#include "CoreMinimal.h"
#include "User.generated.h"

static UMainGameInstance* Main;
namespace System
{
	const float AgroDefaultVolumeRange = 500.f;
	const float ItemDefaultVolumeRange = 50.f;
	const float InteractDefaultVolumeRange = 300.f;
	const float ChaseDefaultMaxDistance = 800.f;
	const float BulletDefaultSpeed = 6000.f;
	const float BulletDefaultVolumeRange = 10.f;
}

UENUM()
enum class EFlickerType : uint8
{
	EFT_None		UMETA(DeplayName = "None"),
	EFT_Default		UMETA(DeplayName = "Default"),
	EFT_Constants			UMETA(DeplayName = "Constants"),
	EFT_Random	UMETA(DeplayName = "Random"),

	EFT_Max		UMETA(DeplayName = "DefaultMax"),
};

UENUM()
enum class EItemType : uint8
{
	EIT_Potion			UMETA(DeplayName = "Potion"),
	EIT_Other			UMETA(DeplayName = "Other"),
	EIT_Bullet			UMETA(DeplayName = "Bullet"),

	EIT_Pistol				UMETA(DeplayName = "Pistol"),
	EIT_AssaultRifle		UMETA(DeplayName = "AssualtRifle"),
	EIT_Shotgun			UMETA(DeplayName = "Shotgun"),
	 
	EIT_Max				UMETA(DeplayName = "DefaultMax")
};
UENUM()
enum class ECharacterState : uint8
{
	ECS_Idle				UMETA(DeplayName = "Idle"),
	ECS_Patrol			UMETA(DeplayName = "Patrol"),
	ECS_Move			UMETA(DeplayName = "Move"),
	ECS_Chase			UMETA(DeplayName = "Chase"),
	ECS_Return			UMETA(DeplayName = "Return"),
	ECS_Combat		UMETA(DeplayName = "Combat"),
	ECS_Death			UMETA(DeplayName = "Death"),

	ECS_Max				UMETA(DeplayName = "DefaultMax")
};

UENUM()
enum class ESprintState : uint8
{
	ESS_Default			UMETA(DeplayName = "Default"),
	ESS_Exhausted		UMETA(DeplayName = "Exhausted"),
	ESS_Fatal				UMETA(DeplayName = "Fatal"),
	ESS_Max				UMETA(DeplayName = "DefaultMax")
};