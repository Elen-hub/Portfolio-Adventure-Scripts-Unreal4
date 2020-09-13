// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "ZombieGirl.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AZombieGirl : public ABaseMonster
{
	GENERATED_BODY()
public:
	AZombieGirl();
	virtual void Tick(float deltaTime) override;
	FORCEINLINE float GetAgroRange() { return mAgroRange; }
protected:
	virtual void BeginPlay() override;
	virtual void OnAgroCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* mCrySound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* mAgroSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* mChaseStartSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	class UAudioComponent* mStepAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	class USoundWave* mStepSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	float mStepTargetRange;
private:
	float mAgroRange;
	float mStepElapsedRange;
};
