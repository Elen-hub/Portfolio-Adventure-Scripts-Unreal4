// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseHero.generated.h"

UCLASS()
class PROJECT_CUBE_API ABaseHero : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseHero();
	float TMaxStamina;
	float TRecoveryStamina;
	float TMouseAxis = 65.f;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpringFunction")
	class USprintFunction* mSprintFunction;
	UPROPERTY(EditAnywhere, Category = "PlayerCamera")
	class UPlayerCameraFunction* mPlayerCamera;
	// Weapon Option
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class ABaseWeapon* mWeapon;

	UClass* mBulletRefClass;

	UPROPERTY(BlueprintReadOnly)
	bool mbIsFire;
	float mAutoFireDelay;

	float mTargetVerticalRecoil;
	float mTargetHorizonRecoil;
	float mCurrRecoil;
	float mElapsedRecoil;

	UPROPERTY(BlueprintReadOnly)
	bool mbIsReloading;
	float mReloadTargetTime;
protected:
	virtual void BeginPlay() override;

	virtual void AttackStart();
	virtual void AttackEnd();
	virtual void Fire();
	virtual void Reload();
	virtual void Interaction();
	virtual void MoveForward(float axis) override;
	virtual void MoveSide(float axis) override;
	virtual void Jump() override;
	virtual void DropWeapon();
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE USprintFunction* SprintFunction() { return mSprintFunction; }
	void GetItem();
	FORCEINLINE ABaseWeapon* GetWeapon() { return mWeapon; }
	void SetWeapon(ABaseWeapon* weapon);
	FORCEINLINE float GetCurrRecoil() { return mCurrRecoil; }
	FORCEINLINE bool IsReloading() { return mbIsReloading; }
	FORCEINLINE bool IsFire() { return mbIsFire; }
};
