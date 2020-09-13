// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PROJECT_CUBE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Overlap Collision")
	class USphereComponent* mOverlapCollision;
	class UAnimMontage* mAnimationMontage;
	UPROPERTY(VisibleAnywhere, Category = "State")
	ECharacterState mCharacterState;
	class UStatFunction* mStatFunction;
	ABaseCharacter* mTarget;

	class UAnimInstance* mAnimInstance;
	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* mCombatMontage;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class UAudioComponent* mAudioComponent;

	// Hit option
	float mHitTargetTime;
	float mHitElapsedTime;
	UPROPERTY(BlueprintReadWrite, Category = "Status")
	bool mbIsHit;

	bool mbIsWalk;
public:
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float TSpeed = 400.f;
	FVector TInputVector;
	FVector TestInitPos;
protected:
	virtual void BeginPlay() override;

	virtual void WalkStart();
	virtual void WalkEnd();
public:
	FORCEINLINE ECharacterState GetCharacterState() { return mCharacterState; }
	FORCEINLINE ABaseCharacter* GetTarget() { return mTarget; }
	FORCEINLINE USphereComponent* GetOverlapCollision() { return mOverlapCollision; }
	FORCEINLINE UStatFunction* StatFunction() { return mStatFunction; }
	FORCEINLINE void SetTarget(ABaseCharacter* character) { mTarget = character; }
	FORCEINLINE bool IsWalk() { return mbIsWalk; }
	virtual void SetCharacterState(const ECharacterState nextState);

	virtual void Tick(float DeltaTime) override;
	virtual void MoveForward(float axis) {};
	virtual void MoveSide(float axis) {};
	virtual void Jump() { Super::Jump(); };
	virtual void SetDamage(float damage);
	virtual void SetHitTime(float hitTime);
	virtual void SetNuckback(FVector direction, float force);
	virtual void Death();
};
