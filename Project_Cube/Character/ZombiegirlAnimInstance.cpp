// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiegirlAnimInstance.h"
#include "ZombieGirl.h"
#include "GameFramework/CharacterMovementComponent.h"

void UZombiegirlAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mCharacter = Cast<AZombieGirl>(TryGetPawnOwner());
}

void UZombiegirlAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!mCharacter)
		return;

	mForwardAxis = mCharacter->GetVelocity().Size();
	mAgroRange = mCharacter->GetAgroRange();
	mbIsInair = mCharacter->GetMovementComponent()->IsFalling();
}