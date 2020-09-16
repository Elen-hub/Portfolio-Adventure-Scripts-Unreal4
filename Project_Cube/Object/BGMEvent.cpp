// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMEvent.h"
#include "Project_Cube/User.h"
#include "Components/BoxComponent.h"

ABGMEvent::ABGMEvent()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ABGMEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (mBGMType == EBGM::None)
		return;

	if (!Cast<ABaseHero>(OtherActor))
		return;

	Main->SoundMng->PlayBGM(this, mBGMType);
}