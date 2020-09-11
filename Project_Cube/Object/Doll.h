// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Doll.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ADoll : public ABaseObject
{
	GENERATED_BODY()
	
public:
	ADoll();
	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doll | Default")
	class USoundWave* mIdleSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doll | Light")
	class ALightObject* mLightlamp;
};
