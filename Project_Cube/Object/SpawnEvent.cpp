// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEvent.h"
#include "Components/BoxComponent.h"

ASpawnEvent::ASpawnEvent()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ASpawnEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (mbUseEventExit)
		return;

	ABaseHero* character = Cast<ABaseHero>(OtherActor);
	if (!character)
		return;

	Spawn();
	mCollision->SetGenerateOverlapEvents(false);
}

void ASpawnEvent::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!mbUseEventExit)
		return;

	ABaseHero* character = Cast<ABaseHero>(OtherActor);
	if (!character)
		return;

	Spawn();
	mCollision->SetGenerateOverlapEvents(false);
}

void ASpawnEvent::Spawn()
{
	if (mSpawnMonsterType)
		Main->SpawnMng->SpawnActor(mSpawnMonsterType, mSpawnLocation, mSpawnRotation);
}