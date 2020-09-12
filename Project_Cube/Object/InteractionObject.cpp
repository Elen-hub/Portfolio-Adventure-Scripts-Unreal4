// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionObject.h"
#include "Components/SphereComponent.h"

AInteractionObject::AInteractionObject()
{
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AInteractionObject::BeginPlay()
{
	Super::BeginPlay();

	if (mInteractionCollision)
		mInteractionCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	if (mCollision)
		mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
}

void AInteractionObject::Tick(float deltatTime)
{
	Super::Tick(deltatTime);
}