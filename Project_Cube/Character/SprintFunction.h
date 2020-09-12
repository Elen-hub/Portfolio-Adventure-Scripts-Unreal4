// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintFunction.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_CUBE_API USprintFunction : public UActorComponent
{
	GENERATED_BODY()

public:	
	FORCEINLINE enum class ESprintState GetSprintState() { return mSprintState; }
	FORCEINLINE bool GetUseSprint() { return mbUseSprint; }
	FORCEINLINE float GetCurrentStamina() { return mCurrStamina; }
	FORCEINLINE float GetStaminaPercent() { return PERCENT(mCurrStamina, *mMaxStamina); }
protected:
	UPROPERTY(VisibleAnywhere)
	ESprintState mSprintState;
private:
	bool mbUseSprint;
	bool mbPossibleSprint;
	float* mRecoveryStamina;
	float* mMaxStamina;
	float mCurrStamina;
	const float mExhaustedStamina = 0.25f;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	USprintFunction* Init();
	void SprintActivate();
	void SprintDeactivate();
	FORCEINLINE void SetPossibleSprint(bool isPossible) { mbPossibleSprint = isPossible; }
};
