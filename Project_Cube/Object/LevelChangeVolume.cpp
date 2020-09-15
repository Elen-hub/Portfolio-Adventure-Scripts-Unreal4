// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChangeVolume.h"
#include "Components/BoxComponent.h"
#include "Project_Cube/Character/BaseHero.h"

ALevelChangeVolume::ALevelChangeVolume()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EventCollision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ALevelChangeVolume::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseHero* hero = Cast<ABaseHero>(OtherActor))
		Main->MapMng->ChangeLevel(hero, mTargetLevel);
}
