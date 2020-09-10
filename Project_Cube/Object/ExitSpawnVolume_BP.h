// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "ExitSpawnVolume_BP.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AExitSpawnVolume_BP : public ABaseObject
{
	GENERATED_BODY()
	
public:
	AExitSpawnVolume_BP();
protected:
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
private:
	void Spawn();
};
