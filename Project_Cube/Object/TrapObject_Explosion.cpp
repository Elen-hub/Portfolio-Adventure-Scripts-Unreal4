// ��ź�� ���� �÷��̾�� ������ ��ƼŬ�� �����Ͽ� �������� ��ü�� ����.


#include "TrapObject_Explosion.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Cube/Character/BaseHero.h"
#include "TimerManager.h"

ATrapObject_Explosion::ATrapObject_Explosion()
{
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());

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
}

void ATrapObject_Explosion::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseHero* character = Cast<ABaseHero>(OtherActor);
	if (!character)
		return;

	character->SetDamage(mDamage);

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

void ATrapObject_Explosion::Explosion()
{
	if (mOverlapParticle)
		GetGameInstance<UMainGameInstance>()->SpawnMng->SpawnParticle(mOverlapParticle, GetActorLocation(), mOverlapParticleSize);
}

void ATrapObject_Explosion::Respawn()
{
	mMesh->SetVisibility(true);
	mCollision->SetGenerateOverlapEvents(true);
}