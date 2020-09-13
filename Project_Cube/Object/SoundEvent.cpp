// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundEvent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

ASoundEvent::ASoundEvent()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ASoundEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!mEnterSound)
		return;

	if (!Cast<ABaseHero>(OtherActor))
		return;

	mAudioComponent->SetSound(mEnterSound);
	mAudioComponent->VolumeMultiplier = Main->SoundMng->GetSFXVolume();
	mAudioComponent->Play();
	if (!mbUseRepeatedlyEnter)
		mCollision->SetGenerateOverlapEvents(false);
}

void ASoundEvent::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!mExitSound)
		return;

	if (!Cast<ABaseHero>(OtherActor))
		return;

	mAudioComponent->SetSound(mExitSound);
	mAudioComponent->VolumeMultiplier = Main->SoundMng->GetSFXVolume();
	mAudioComponent->Play();
	if (!mbUseRepeatedlyExit)
		mCollision->SetGenerateOverlapEvents(false);
}