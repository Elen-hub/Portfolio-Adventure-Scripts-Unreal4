// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/Object/Bullet.h"
#include "CoreMinimal.h"
#include "Item.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ABaseWeapon : public AItem
{
	GENERATED_BODY()
	


public:
	ABaseWeapon();

	void ActivateCollision(bool isActivate);
	void Fire(FVector muzzleLocation, FVector direction);
	void PlayReloadSound();
	void PlayEmptyShotSound();
protected:
	virtual ABaseWeapon* Init();

public:
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	int MaxMagazine;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	int CurrMagazine;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	float Damage;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	float FullAutoSpeed;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	float ReloadSpeed;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	float Recoil;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	float MaxRecoil;
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	float BulletSpread;

protected:
	UClass* mBulletRefClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundWave* mGetSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	USoundWave* mFireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	USoundWave* mReloadSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	USoundWave* mDropSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	USoundWave* mEmptyShotSound;
};
