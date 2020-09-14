// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "Project_Cube/Character/BaseCharacter.h"
#include "CoreMinimal.h"
/**
 * 
 */
class PROJECT_CUBE_API BaseState
{
protected:
	ABaseCharacter* mCharacter;
	AAIController* mAIController;
	UAnimInstance* mAnimInstance;
public:
	virtual BaseState* Init(ABaseCharacter* targetCharacter)
	{
		mCharacter = targetCharacter;
		mAnimInstance = mCharacter->GetMesh()->GetAnimInstance();
		mAIController = Cast<AAIController>(targetCharacter->GetController());
		return this;
	};
	virtual void OnStateBegin() {};
	virtual void OnStateStay() {};
	virtual void OnStateExit() {};
};