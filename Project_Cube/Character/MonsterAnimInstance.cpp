// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mBaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!mBaseCharacter)
		return;

	mForwardAxis = mBaseCharacter->GetVelocity().Size();
	mbIsInair = mBaseCharacter->GetMovementComponent()->IsFalling();
}