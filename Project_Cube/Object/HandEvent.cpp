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
	if (mTickElapsedTime > 8)
	{
		if (!mbSound)
		{
			mbSound = true;
			// 사운드재생
		}
	}
	if (mTickElapsedTime > 10)
	{
		float x = 0.f, y = 0.f, z = 0.f;
		FRotator rot = FRotator::ZeroRotator;
		switch (FMath::RandRange(0, 2))
		{
		case 0:
			x = FMath::RandRange(-870, 770);
			y = -170.f;
			z = FMath::RandRange(-20, 180);
			rot = FRotator(0, 270, FMath::RandRange(0, 360));
			break;
		case 1:
			x = FMath::RandRange(-870, 770);
			y = 100.f;
			z = FMath::RandRange(-20, 180);
			rot = FRotator(0, 90, FMath::RandRange(0, 360));
			break;
		case 2:
			x = FMath::RandRange(-880, 780);
			y = FMath::RandRange(-140, 110);
			z = -50.f;
			rot = FRotator(-90, 0, FMath::RandRange(0, 360));
			break;
		}
		FActorSpawnParameters SpawnParams;
		SpawnParams.Template = mDecalActors;
		ADecalActor* decal = GetWorld()->SpawnActor <ADecalActor>(mDecalActors->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		decal->SetActorLocationAndRotation(FVector(x, y, z), rot);
		decal->SetActorScale3D(FVector::OneVector * FMath::RandRange(0.8f, 1.2f));
	}
	if (mTickElapsedTime > 15.f)
	{
		if (!mbSpawn)
		{
			mbSpawn = true;
			// spawn
		}
	}
}

void AHandEvent::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;

	mbStart = true;
	mCollision->SetGenerateOverlapEvents(false);
}