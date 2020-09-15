// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "HandEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AHandEvent : public ABaseObject
{
	GENERATED_BODY()
	
public:
	AHandEvent();
	virtual void Tick(float deltaTime) override;

protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	class ADecalActor* mDecalActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	TArray<class ALightObject*> mLightObjects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	class USoundWave* mSound;
private:
	bool mbStart;
	float mTickElapsedTime;
	float mHandleInstanceTargetTime = 0.15f;
	float mHandleInstanceElapsedTime;
};
