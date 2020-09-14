// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "Spider.generated.h"

/**
 * 
 */

UENUM()
enum class ESpiderAttackCollisionType : uint8
{
	None,
	Left,
	Right,
	All,
};

UCLASS()
class PROJECT_CUBE_API ASpider : public ABaseMonster
{
	GENERATED_BODY()

public:
	ASpider();
	virtual void Tick(float deltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SetActiveAttackCollision(const ESpiderAttackCollisionType activateCollisionType);
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack | Collision")
	class UBoxComponent* mLeftWeaponCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack | Collision")
	class UBoxComponent* mRightWeaponCollision;
	UFUNCTION()
	void OnAttackCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
