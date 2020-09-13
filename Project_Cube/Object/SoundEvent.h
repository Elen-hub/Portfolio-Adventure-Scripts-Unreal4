// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "BaseObject.h"
#include "SoundEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ASoundEvent : public ABaseObject
{
	GENERATED_BODY()
	
public:
	ASoundEvent();
protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Enter")
	class USoundWave* mEnterSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Enter")
	bool mbUseRepeatedlyEnter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Exit")
		class USoundWave* mExitSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Exit")
	bool mbUseRepeatedlyExit;
};
