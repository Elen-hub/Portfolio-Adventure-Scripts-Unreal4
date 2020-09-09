// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAnimInstance.h"
#include "BaseHero.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mBaseHero = Cast<ABaseHero>(TryGetPawnOwner());
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!mBaseHero)
		return;

	mbHaveWeapon = mBaseHero->GetWeapon() != nullptr;
}