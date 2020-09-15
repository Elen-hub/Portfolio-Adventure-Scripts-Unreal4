// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "LevelChangeVolume.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ALevelChangeVolume : public ABaseObject
{
	GENERATED_BODY()

public:
	ALevelChangeVolume();
protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	ELevel mTargetLevel;
};
