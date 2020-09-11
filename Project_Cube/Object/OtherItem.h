// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "OtherItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AOtherItem : public AItem
{
	GENERATED_BODY()
	
public:
	AOtherItem();
	virtual void Tick(float deltaTime) override;
	virtual void GetItem() override;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, Category = "Trap | Particle")
	class UParticleSystemComponent* mParticleIdle;
};
