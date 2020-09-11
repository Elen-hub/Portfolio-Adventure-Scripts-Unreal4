// Fill out your copyright notice in the Description page of Project Settings.


#include "Doll.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "LightObject.h"

ADoll::ADoll()
{
	USphereComponent* sphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	sphereCollision->SetupAttachment(GetRootComponent());
	mCollision = sphereCollision;
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}
void ADoll::BeginPlay()
{
	Super::BeginPlay();

	if (mIdleSound)
	{
		mAudioComponent->SetSound(mIdleSound);
		mAudioComponent->Play();
	}
}

void ADoll::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ADoll::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mCollision->SetGenerateOverlapEvents(false);
	if (!Cast<ABaseHero>(OtherActor))
		return;
	
	mAudioComponent->Stop();
	Main->SoundMng->PlayEventSound(this, EEventSound::SurpriseLow);

	SetDelayTimer(mLightlamp, &ALightObject::SwitchOn);
}

void ADoll::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
