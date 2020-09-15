// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "Project_Cube/GameInstance/MainGameInstance.h"
#include "Project_Cube/GameInstance/UIMng.h"
#include "Project_Cube/GameInstance/CharacterMng.h"
#include "Project_Cube/GameInstance/SpawnMng.h"
#include "Project_Cube/GameInstance/SoundMng.h"
#include "Project_Cube/GameInstance/MapMng.h"
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

namespace Lib
{
	static const FRotator GetLookAtRotator(FVector const& from, FVector const& to, FVector upVector, bool holdZ = true)
	{
		FVector forwardVector = to - from;
		if (holdZ) forwardVector.Z = 0;
		forwardVector = forwardVector.GetSafeNormal();
		upVector = upVector - (forwardVector * FVector::DotProduct(upVector, forwardVector));
		upVector = upVector.GetSafeNormal();

		FVector vector = forwardVector.GetSafeNormal();
		FVector vector2 = FVector::CrossProduct(upVector, vector);
		FVector vector3 = FVector::CrossProduct(vector, vector2);
		float m00 = vector.X;
		float m01 = vector.Y;
		float m02 = vector.Z;
		float m10 = vector2.X;
		float m11 = vector2.Y;
		float m12 = vector2.Z;
		float m20 = vector3.X;
		float m21 = vector3.Y;
		float m22 = vector3.Z;

		float num8 = (m00 + m11) + m22;
		FQuat quaternion = FQuat();

		FRotator rot;

		if (num8 > 0.0f)
		{
			float num = (float)FMath::Sqrt(num8 + 1.0f);
			quaternion.W = num * 0.5f;
			num = 0.5f / num;
			quaternion.X = (m12 - m21) * num;
			quaternion.Y = (m20 - m02) * num;
			quaternion.Z = (m01 - m10) * num;
			rot = FRotator(quaternion);
		}

		if ((m00 >= m11) && (m00 >= m22))
		{
			float num7 = (float)FMath::Sqrt(((1.0f + m00) - m11) - m22);
			float num4 = 0.5f / num7;
			quaternion.X = 0.5f * num7;
			quaternion.Y = (m01 + m10) * num4;
			quaternion.Z = (m02 + m20) * num4;
			quaternion.W = (m12 - m21) * num4;
			rot = FRotator(quaternion);
		}

		if (m11 > m22)
		{
			float num6 = (float)FMath::Sqrt(((1.0f + m11) - m00) - m22);
			float num3 = 0.5f / num6;
			quaternion.X = (m10 + m01) * num3;
			quaternion.Y = 0.5f * num6;
			quaternion.Z = (m21 + m12) * num3;
			quaternion.W = (m20 - m02) * num3;
			rot = FRotator(quaternion);
		}

		float num5 = (float)FMath::Sqrt(((1.0f + m22) - m00) - m11);
		float num2 = 0.5f / num5;
		quaternion.X = (m20 + m02) * num2;
		quaternion.Y = (m21 + m12) * num2;
		quaternion.Z = 0.5f * num5;
		quaternion.W = (m01 - m10) * num2;
		rot = FRotator(quaternion);

		return rot;
	}

	static bool IsPrimitiveComponentRenderedRecently(UPrimitiveComponent* _PrimitiveComponent, float _Tolerance)
	{
		if (_PrimitiveComponent == nullptr)
			return false;

		UWorld* World = _PrimitiveComponent->GetWorld();
		return (World) ? (World->GetTimeSeconds() - _PrimitiveComponent->GetLastRenderTimeOnScreen() <= _Tolerance) : false;
	}
}