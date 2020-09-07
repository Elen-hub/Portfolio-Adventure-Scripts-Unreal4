// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!BaseCharacter)
		return;

	FVector velocity = BaseCharacter->TInputVector;
	mForwardAxis = velocity.X;
	mSideAxis = velocity.Y;

	mbIsInair = BaseCharacter->GetMovementComponent()->IsFalling();
}