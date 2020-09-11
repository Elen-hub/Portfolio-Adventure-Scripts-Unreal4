// Fill out your copyright notice in the Description page of Project Settings.

DECLARE_DELEGATE(TimerDelegate);

#include "BaseObject.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ABaseObject::ABaseObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(mMesh);

	mAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	mAudioComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	// 오버랩 바인딩
	
	if (mCollision)
	{
		mCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseObject::OnCollisionEnter);
		mCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseObject::OnCollisionExit);
	}
}
template< class T >
void ABaseObject::SetDelayTimer(T* inObj, void (T::* inMethod)())
{
	if (mbUseDelay)
		GetWorldTimerManager().SetTimer(mDelayTimer, inObj, inMethod, mDelayTime);
	else
		(inObj->*inMethod)();
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

