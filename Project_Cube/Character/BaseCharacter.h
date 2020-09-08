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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* mMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Overlap Collision")
	class USphereComponent* mOverlapCollision;
	class UAnimMontage* mAnimationMontage;
	UPROPERTY(VisibleAnywhere, Category = "State")
	ECharacterState mCharacterState;
	class UStatFunction* mStatFunction;
	ABaseCharacter* mTarget;

	// Hit option
	float mHitTargetTime;
	float mHitElapsedTime;
	UPROPERTY(BlueprintReadWrite, Category = "Status")
	bool mbIsHit;
public:
	ABaseCharacter();

	float TSpeed = 400.f;
	FVector TInputVector;
	FVector TestInitPos;
protected:
	virtual void BeginPlay() override;
public:
	FORCEINLINE ECharacterState GetCharacterState() { return mCharacterState; }
	FORCEINLINE ABaseCharacter* GetTarget() { return mTarget; }
	FORCEINLINE USphereComponent* GetOverlapCollision() { return mOverlapCollision; }
	FORCEINLINE UStatFunction* StatFunction() { return mStatFunction; }
	FORCEINLINE void SetTarget(ABaseCharacter* character) { mTarget = character; }
	virtual void SetCharacterState(const ECharacterState nextState);

	virtual void Tick(float DeltaTime) override;
	virtual void MoveForward(float axis) {};
	virtual void MoveSide(float axis) {};
	virtual void Jump() { Super::Jump(); };
	virtual void SetDamage(float damage);
	virtual void SetHitTime(float hitTime);
	virtual void SetNuckback(float force);
	virtual void Death();
};
