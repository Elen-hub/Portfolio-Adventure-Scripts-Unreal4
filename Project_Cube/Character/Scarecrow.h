// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "Scarecrow.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AScarecrow : public ABaseMonster
{
	GENERATED_BODY()

public:
	AScarecrow();
	virtual void Tick(float deltaTime) override;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnAgroCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* mRotatorSound;
};
