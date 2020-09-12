// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionObject.h"

void AInteractionObject::BeginPlay()
{
	Super::BeginPlay();

	if (mInteractionCollision)
		mInteractionCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	if (mCollision)
		mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
}