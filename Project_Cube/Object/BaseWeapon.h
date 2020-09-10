// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
protected:
	bool mbIsEquip;

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

	void ActivateCollision(bool isActivate);
	void Equip();
	void Unequip();
	void Reload(float magazine);
};
