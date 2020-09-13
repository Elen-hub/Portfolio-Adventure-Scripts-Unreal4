// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombiegirlAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UZombiegirlAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
		class AZombieGirl* mCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		float mForwardAxis;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		float mAgroRange;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		bool mbIsInair;
};
