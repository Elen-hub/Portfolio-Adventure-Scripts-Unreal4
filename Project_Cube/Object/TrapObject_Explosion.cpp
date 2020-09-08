// ��ź�� ���� �÷��̾�� ������ ��ƼŬ�� �����Ͽ� �������� ��ü�� ����.


#include "TrapObject_Explosion.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Cube/Character/BaseHero.h"
#include "TimerManager.h"

ATrapObject_Explosion::ATrapObject_Explosion()
{
	mOverlapRadius = 75.f;

	USphereComponent* sphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	mCollision = sphereCollision;
	mCollision->SetupAttachment(GetRootComponent());
	sphereCollision->InitSphereRadius(mOverlapRadius);

	mParticleIdle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Idle Particle"));
	mParticleIdle->SetupAttachment(GetRootComponent());

	mbUseRespawn = false;
	mRespawnTime = 0.f;
	mDamage = 0.f;

	mOverlapParticleSize = 1.f;
}

void ATrapObject_Explosion::BeginPlay()
{
	Super::BeginPlay();

	// �������ݸ��� ���� (�̺�Ʈ�����, Ÿ���� ���彺��ƽ, �浹����� ���� ��ĥ����)
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Cast<USphereComponent>(mCollision)->SetSphereRadius(mOverlapRadius);
}

void ATrapObject_Explosion::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseHero* character = Cast<ABaseHero>(OtherActor);
	if (!character)
		return;

	const FVector direction = (OtherActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	character->SetDamage(mDamage);
	character->SetNuckback(direction, mNuckbackForce);

	// ������ ������ �̺�Ʈ�� ��������
	mCollision->SetGenerateOverlapEvents(false);

	if (mbUseDelay)
	{
		GetWorldTimerManager().SetTimer(mDelayTimer, this, &ATrapObject_Explosion::Explosion, mDelayTime);
	}
	else
	{
		Explosion();
	}
}

void ATrapObject_Explosion::Explosion()
{
	if (mOverlapParticle)
		GetGameInstance<UMainGameInstance>()->SpawnMng->SpawnParticle(mOverlapParticle, GetActorLocation(), mOverlapParticleSize);

	// ��������� ���.
	if (mbUseRespawn)
	{
		// ������ ������ �̺�Ʈ�� �����ʰ� �޽��� ������ �ʰ���.
		mMesh->SetVisibility(false);
		GetWorldTimerManager().SetTimer(mRespawnTimer, this, &ATrapObject_Explosion::Respawn, mRespawnTime);
	}
	else
	{
		Destroy();
	}
}

void ATrapObject_Explosion::Respawn()
{
	mMesh->SetVisibility(true);
	mCollision->SetGenerateOverlapEvents(true);
}