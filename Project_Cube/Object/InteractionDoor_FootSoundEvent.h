// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionDoor.h"
#include "InteractionDoor_FootSoundEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AInteractionDoor_FootSoundEvent : public AInteractionDoor
{
	GENERATED_BODY()
	
public:
	AInteractionDoor_FootSoundEvent();

protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
