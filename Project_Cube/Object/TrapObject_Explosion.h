// 폭탄과 같은 플레이어와 닿으면 파티클을 생성하여 데미지를 물체를 정의.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "TrapObject_Explosion.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_CUBE_API ATrapObject_Explosion : public ABaseObject
{
	GENERATED_BODY()

public:
	ATrapObject_Explosion();
protected:
	UPROPERTY(EditAnywhere, Category = "Trap | Particle")
	class UParticleSystemComponent* mParticleIdle;

	UPROPERTY(EditAnywhere, Category = "Trap | Particle")
	class UParticleSystem* mParticleOverlap;

	UPROPERTY(EditAnywhere, Category = "Trap | Particle")
	float mParticleOverlapSize;

	UPROPERTY(EditAnywhere, Category = "Trap | Damage")
	float mDamage;

	UPROPERTY(EditAnywhere, Category = "Trap | Damage")
	bool mbUseDelay;

	UPROPERTY(EditAnywhere, Category = "Trap | Damage")
	float mDelayTime;

	UPROPERTY(EditAnywhere, Category = "Trap | Respawn")
	bool mbUseRespawn;

	UPROPERTY(EditAnywhere, Category = "Trap | Respawn")
	float mRespawnTime;

	FTimerHandle mDelayTimer;
	FTimerHandle mRespawnTimer;
protected:
	virtual void BeginPlay() override;
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void Explosion();
	void Respawn();
};
