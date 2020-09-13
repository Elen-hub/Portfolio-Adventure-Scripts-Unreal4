// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
		class ABaseCharacter* mBaseCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float mForwardAxis;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool mbIsInair;
};
