// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.h"
#include "BaseHero.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mBaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!mBaseCharacter)
		return;

	FVector velocity = mBaseCharacter->TInputVector;
	mForwardAxis = velocity.X;
	mSideAxis = velocity.Y;

	mbIsInair = mBaseCharacter->GetMovementComponent()->IsFalling();
}