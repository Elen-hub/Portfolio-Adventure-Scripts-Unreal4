// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherItem.h"
#include "Particles/ParticleSystemComponent.h"

AOtherItem::AOtherItem()
{
	mParticleSize = 1.f;
	mParticleIdle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Idle Particle"));
	mParticleIdle->SetupAttachment(GetRootComponent());
}

void AOtherItem::BeginPlay()
{
	Super::BeginPlay();

	mParticleIdle->SetWorldScale3D(FVector::OneVector * mParticleSize);
}

void AOtherItem::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AOtherItem::GetItem()
{
	Super::GetItem();
}
