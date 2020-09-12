// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionDoor_FootSoundEvent.h"
#include "Components/BoxComponent.h"

AInteractionDoor_FootSoundEvent::AInteractionDoor_FootSoundEvent()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AInteractionDoor_FootSoundEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
void AInteractionDoor_FootSoundEvent::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}