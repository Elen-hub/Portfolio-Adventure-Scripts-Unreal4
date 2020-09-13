// Fill out your copyright notice in the Description page of Project Settings.


#include "Doll.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshActor.h"
#include "LightObject.h"
#include "Item.h"

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

	if (mItem != nullptr)
	{
		if (mItem->IsHidden())
		{
			mItem = nullptr;
			if (mWheelChair != nullptr)
			{
				SetActorLocation(mMoveChairPos);
				SetActorRotation(mMoveChairRot);
				AddActorLocalOffset(FVector(0, 0, 50.f));
				AddActorWorldRotation(FRotator(0, -90.f, 0));
				
				mLightlamp->Broken();
				mWheelChair->SetActorLocation(mMoveChairPos);
				mWheelChair->SetActorRotation(mMoveChairRot);
				mAudioComponent->SetSound(mChairSound);
				mAudioComponent->Play();
			}
		}
	}
	else
	{
		if (Lib::IsPrimitiveComponentRenderedRecently(mMesh, deltaTime))
			mAudioComponent->Stop();
	}
}

void ADoll::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mCollision->SetGenerateOverlapEvents(false);
	if (!Cast<ABaseHero>(OtherActor))
		return;
	
	mAudioComponent->StopDelayed(mDelayTime-0.5f);
	Main->SoundMng->PlayEventSound(this, EEventSound::SurpriseLow);

	SetDelayTimer(mLightlamp, &ALightObject::SwitchOn);
}

void ADoll::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != mItem)
		return;
}
