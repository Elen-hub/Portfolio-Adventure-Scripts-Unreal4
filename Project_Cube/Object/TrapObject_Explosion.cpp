// 폭탄과 같은 플레이어와 닿으면 파티클을 생성하여 데미지를 물체를 정의.


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

	// 오버랩콜리전 설정 (이벤트만사용, 타입은 월드스태틱, 충돌관계는 폰과 겹칠때만)
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

	// 리스폰 전까진 이벤트를 받지않음
	mCollision->SetGenerateOverlapEvents(false);

	if (mbUseDelay)
	{
		GetWorldTimerManager().SetTimer(mDelayTimer, this, &ATrapObject_Explosion::Explosion, mDelayTime);
	}
	else
	{
		Explosion();
	}

	// 리스폰기능 사용.
	if (mbUseRespawn)
	{
		// 리스폰 전까진 이벤트를 받지않고 메쉬를 보이지 않게함.
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