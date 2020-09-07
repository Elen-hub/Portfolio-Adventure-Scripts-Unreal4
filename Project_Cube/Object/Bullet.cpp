// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Cube/User.h"
#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABullet::ABullet()
{
	// 기본콜리전 설정
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	RootComponent = mCollision;
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	USphereComponent* sphere = Cast<USphereComponent>(mCollision);
	sphere->InitSphereRadius(System::BulletDefaultVolumeRange);

	// 총알 운동제어 초기화
	mMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	mMovementComponent->SetUpdatedComponent(mCollision);
	mMovementComponent->InitialSpeed = System::BulletDefaultSpeed;
	mMovementComponent->MaxSpeed = System::BulletDefaultSpeed;
	mMovementComponent->bRotationFollowsVelocity = true;
	mMovementComponent->bShouldBounce = true;
	mMovementComponent->Bounciness = 0.3f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::Enabled(FVector spawnPos, FVector direction, float speed, float damage, float hitTime)
{
	SetActorLocation(spawnPos);
	mCollision->SetGenerateOverlapEvents(true);
	mMovementComponent->Velocity = direction * mMovementComponent->InitialSpeed;
}

void ABullet::Disabled()
{
	mCollision->SetGenerateOverlapEvents(false);
	mMovementComponent->Velocity = FVector::ZeroVector;
}

void ABullet::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
