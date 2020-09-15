// Fill out your copyright notice in the Description page of Project Settings.


#include "HandEvent.h"
#include "Components/BoxComponent.h"
#include "LightObject.h"
#include "Components/AudioComponent.h"
#include "Engine/DecalActor.h"

AHandEvent::AHandEvent()
{
	mTickElapsedTime = 0.f;

	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Collision"));
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AHandEvent::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (!mbStart)
		return;

	mTickElapsedTime += deltaTime * 1.5f;

	if (mTickElapsedTime > 9 - mLightObjects.Num())
	{
		if (mLightObjects.Num()> 0)
		{
			ALightObject* obj = mLightObjects[FMath::RandRange(0, mLightObjects.Num() - 1)];
			obj->Broken();
			mLightObjects.Remove(obj);
		}
	}

	if (mTickElapsedTime > 10)
	{
		mHandleInstanceElapsedTime += deltaTime;
		if (mHandleInstanceTargetTime < mHandleInstanceElapsedTime)
		{
			mAudioComponent->Play();
			mHandleInstanceElapsedTime = 0;

			float x = 0.f, y = 0.f, z = 0.f;
			FVector rot = FVector::ZeroVector;
			switch (FMath::RandRange(0, 2))
			{
			case 0:
				x = FMath::RandRange(-870, 770);
				y = -170.f;
				z = FMath::RandRange(-20, 180);
				rot = FVector(FMath::RandRange(0, 360), 0, 270);
				break;
			case 1:
				x = FMath::RandRange(-870, 770);
				y = 100.f;
				z = FMath::RandRange(-20, 180);
				rot = FVector(FMath::RandRange(0, 360), 0, 90);
				break;
			case 2:
				x = FMath::RandRange(-880, 780);
				y = FMath::RandRange(-140, 110);
				z = -50.f;
				rot = FVector(FMath::RandRange(0, 360), -90, 0);
				break;
			}
			FActorSpawnParameters SpawnParams;
			SpawnParams.Template = mDecalActors;
			ADecalActor* decal = GetWorld()->SpawnActor <ADecalActor>(mDecalActors->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			decal->SetActorLocationAndRotation(FVector(x, y, z), rot.Rotation());
			// decal->GetDecal()->Si
		}
	}
}

void AHandEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;

	mAudioComponent->SetSound(mSound);
	mbStart = true;
	mCollision->SetGenerateOverlapEvents(false);
}