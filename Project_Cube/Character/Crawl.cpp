// Fill out your copyright notice in the Description page of Project Settings.


#include "Crawl.h"
#include "Components/SphereComponent.h"
#include "Project_Cube/StateMachine/Chase_Gradually.h"
#include "Project_Cube/StateMachine/Idle_Wait.h"
#include "Project_Cube/UI/MainUI.h"


ACrawl::ACrawl()
{
	mEventCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	mEventCollision->SetupAttachment(GetRootComponent());
	mEventCollision->InitSphereRadius(150.f);
	mEventCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mEventCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	mEventCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mEventCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
}

void ACrawl::BeginPlay()
{
	Super::BeginPlay();

	Idle_Wait* idleState = new Idle_Wait();
	idleState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Idle, idleState);
	Chase_Gradually* chaseState = new Chase_Gradually();
	chaseState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Chase, chaseState);

	mEventCollision->OnComponentBeginOverlap.AddDynamic(this, &ACrawl::OnTextureEvent);
}

void ACrawl::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ACrawl::OnTextureEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ABaseHero>(OtherActor))
		return;

	mEventCollision->SetGenerateOverlapEvents(false);

	Main->UIMng->Get<UMainUI>(EUIType::MainUI)->SetTexture(mEventTexture);
	Main->UIMng->Get<UMainUI>(EUIType::MainUI)->ActivateTexture(true);
	Main->SoundMng->PlayEventSound(this, EEventSound::GraduallyHigh);
}