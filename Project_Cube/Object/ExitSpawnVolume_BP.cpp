// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitSpawnVolume_BP.h"
#include "Components/BoxComponent.h"


AExitSpawnVolume_BP::AExitSpawnVolume_BP()
{
	UBoxComponent* boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision = boxCollision;
	mCollision->SetupAttachment(GetRootComponent());
}

void AExitSpawnVolume_BP::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABaseHero* character = Cast<ABaseHero>(OtherActor);
	if (!character)
		return;

	mCollision->SetGenerateOverlapEvents(false);
}

void AExitSpawnVolume_BP::Spawn()
{

}