// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Cube/User.h"
#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Project_Cube/Character/BaseMonster.h"

ABullet::ABullet()
{
	// �⺻�ݸ��� ����
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	RootComponent = mCollision;
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	mCollision->SetGenerateOverlapEvents(true);
	USphereComponent* sphere = Cast<USphereComponent>(mCollision);
	sphere->InitSphereRadius(System::BulletDefaultVolumeRange);

	// �Ѿ� ����� �ʱ�ȭ
	mMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	mMovementComponent->SetUpdatedComponent(mCollision);
	mMovementComponent->InitialSpeed = System::BulletDefaultSpeed;
	mMovementComponent->MaxSpeed = System::BulletDefaultSpeed;
	mMovementComponent->bRotationFollowsVelocity = true;
	mMovementComponent->bShouldBounce = false;
	mMovementComponent->ProjectileGravityScale = 1.f;
	// mMovementComponent->Bounciness = 0.3f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	mDistanceAmount += mMovementComponent->InitialSpeed * deltaTime;
	if (mDistanceAmount > 40000.f)
		Disabled();

}

void ABullet::Enabled(FVector spawnPos, FVector direction, float speed, float damage, float hitTime)
{
	mDistanceAmount = 0;

	mDamage = damage;
	mHitTime = hitTime;
	SetActorLocation(spawnPos);
	mMovementComponent->Velocity = direction * mMovementComponent->InitialSpeed;
	mMovementComponent->Activate();
	SetActorHiddenInGame(false);
}

void ABullet::Disabled()
{
	mMovementComponent->Velocity = FVector::ZeroVector;
	mMovementComponent->Deactivate();
	SetActorHiddenInGame(true);
}

void ABullet::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetGameInstance<UMainGameInstance>()->SpawnMng->SpawnParticle(mOverlapParticle, SweepResult.Location, mOverlapParticleScale);
	ABaseMonster* monster = Cast<ABaseMonster>(OtherActor);
	if (monster != nullptr)
	{
		monster->SetDamage(mDamage);

		TArray<FHitResult> HitInfo;
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(this);
		FCollisionObjectQueryParams objectParams = FCollisionObjectQueryParams::AllDynamicObjects;
		GetWorld()->LineTraceMultiByObjectType(HitInfo, OverlappedComponent->GetComponentLocation(), OtherComp->GetComponentLocation(), objectParams, queryParams);
		for (FHitResult result : HitInfo)
		{
			if (ABaseCharacter* hitActor = Cast<ABaseCharacter>(result.GetActor()))
			{
				hitActor->SetHitEffect(result.ImpactPoint, result.ImpactNormal);
				return;
			}
		}
	}
}
