// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "SpawnEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ASpawnEvent : public ABaseObject
{
	GENERATED_BODY()

public:
	ASpawnEvent();
protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
private:
	void Spawn();

protected:
	// true = Exit , false = Enter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Default")
	bool mbUseEventExit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event | Spawn")
	TSubclassOf<class ABaseMonster> mSpawnMonsterType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Spawn")
	FVector mSpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Spawn")
	FRotator mSpawnRotation;
};
