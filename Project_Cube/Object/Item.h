// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AItem : public ABaseObject
{
	GENERATED_BODY()

public:
	AItem();
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	FString Name;
protected:
	UPROPERTY(EditAnywhere, Category = "Item | Stat")
	EItemType mItemType;
	
public:
	virtual AItem* Init();
	virtual void GetItem();
	virtual void SpawnItem() {};
	FORCEINLINE EItemType GetWeaponType() { return mItemType; }
	virtual FText GetItemSelectText();
	EItemType GetItemType() { return mItemType; }
	bool IsEquip() { return !mCollision->GetGenerateOverlapEvents(); }
};
