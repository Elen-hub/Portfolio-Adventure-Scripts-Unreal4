// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ABullet : public ABaseObject
{
	GENERATED_BODY()
	
public:
	ABullet();
private:
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* mMovementComponent;
protected:
	virtual void BeginPlay() override;

public:
	void Enabled(FVector spawnPos, FVector direction, float speed, float damage, float hitTime);
	void Disabled();
	void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
