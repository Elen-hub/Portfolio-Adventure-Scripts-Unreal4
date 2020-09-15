// Fill out your copyright notice in the Description page of Project Settings.


#include "TextureEvent.h"
#include "Components/BoxComponent.h"
#include "Project_Cube/UI/MainUI.h"

ATextureEvent::ATextureEvent()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ATextureEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;

	Main->UIMng->Get<UMainUI>(EUIType::MainUI)->ActivateTexture(true);
}

void ATextureEvent::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;

	Main->UIMng->Get<UMainUI>(EUIType::MainUI)->ActivateTexture(false);
	Destroy();
}
