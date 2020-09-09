// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseObject::ABaseObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(mMesh);
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

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

