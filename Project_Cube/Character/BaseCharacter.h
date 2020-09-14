// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UENUM()
enum class ECharacterSoundType : uint8
{
	Idle,
	Move,
	Hit,
	Death,

	Max,
};

UCLASS()
class PROJECT_CUBE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void SetCharacterState(const ECharacterState nextState);
	virtual void PlaySound(const ECharacterSoundType sound);
	virtual void PlaySound(class USoundWave* sound);
	virtual void StopSound();

	virtual void Tick(float DeltaTime) override;
	virtual void MoveForward(float axis) {};
	virtual void MoveSide(float axis) {};
	virtual void Jump() { Super::Jump(); };
	virtual void SetDamage(float damage);
	virtual void SetHitTime(float hitTime);
	virtual void SetHitEffect(FVector hitPoint, FVector directionVector);
	virtual void SetNuckback(FVector direction, float force);
	virtual void Death();

protected:
	virtual void BeginPlay() override;

	virtual void WalkStart();
	virtual void WalkEnd();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Overlap Collision")
	class USphereComponent* mOverlapCollision;
	class UAnimMontage* mAnimationMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	ECharacterState mCharacterState;
	class UStatFunction* mStatFunction;
	ABaseCharacter* mTarget;

	class UAnimInstance* mAnimInstance;
	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* mCombatMontage;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class UAudioComponent* mAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	UParticleSystem* mHitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float mHitParticleSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* mIdleSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundWave* mAttackSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundWave* mDeathSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundWave* mHitSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundWave* mMoveSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float mStepSoundTargetTime;

	TMap<ECharacterSoundType, USoundWave*> mCharacterSoundMap;

	// Combat option
	float mHitTargetTime;
	float mHitElapsedTime;
	UPROPERTY(BlueprintReadWrite, Category = "Status")
	bool mbIsHit;
	float mAttackElapsedTime;

	bool mbIsWalk;

	TArray<ABaseCharacter*> mAttackList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float TSpeed = 400.f;
	float TRange = 100.f;
	FVector TInputVector;
	FVector TestInitPos;

	FORCEINLINE ECharacterState GetCharacterState() { return mCharacterState; }
	FORCEINLINE ABaseCharacter* GetTarget() { return mTarget; }
	FORCEINLINE USphereComponent* GetOverlapCollision() { return mOverlapCollision; }
	FORCEINLINE UStatFunction* StatFunction() { return mStatFunction; }
	FORCEINLINE void SetTarget(ABaseCharacter* character) { mTarget = character; }
	FORCEINLINE bool IsWalk() { return mbIsWalk; }
	FORCEINLINE float GetStepSoundTargetTime() { return mStepSoundTargetTime; }
	FORCEINLINE void ClearAttackList() { mAttackList.Empty(); }
	FORCEINLINE UAnimMontage* GetCombatMontage() { return mCombatMontage; }
	FORCEINLINE bool IsHit() { return mbIsHit; }
	FORCEINLINE void SetAttackTime(float time) { mAttackElapsedTime += time; }
	FORCEINLINE bool IsPossibleAttack() { return mAttackElapsedTime <= 0; }
};
