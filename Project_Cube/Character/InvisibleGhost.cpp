// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleGhost.h"

#include "Project_Cube/StateMachine/BaseState.h"
#include "Project_Cube/StateMachine/Chase_Forever.h"
#include "Project_Cube/StateMachine/Idle_Default.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Project_Cube/Object/LightObject.h"

AInvisibleGhost::AInvisibleGhost()
{
	mBrokenLampOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	mBrokenLampOverlap->SetupAttachment(GetRootComponent());
	mBrokenLampOverlap->InitSphereRadius(150.f);
	mBrokenLampOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mBrokenLampOverlap->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	mBrokenLampOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mBrokenLampOverlap->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
}

void AInvisibleGhost::BeginPlay()
{
	Super::BeginPlay();

	mBrokenLampOverlap->OnComponentBeginOverlap.AddDynamic(this, &AInvisibleGhost::OnBrokenEvent);

	Idle_Default* idleState = new Idle_Default();
	idleState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Idle, idleState);
	Chase_Forever* chaseState = new Chase_Forever();
	chaseState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Chase, chaseState);
}

void AInvisibleGhost::OnBrokenEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ALightObject* light = Cast<ALightObject>(OtherActor))
	{
		light->Broken();
	}
}