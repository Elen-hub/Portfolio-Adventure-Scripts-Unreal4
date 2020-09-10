// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "LightObject.generated.h"

DECLARE_DELEGATE_RetVal(float, FlickerAction)

UCLASS()
class PROJECT_CUBE_API ALightObject : public ABaseObject
{
	GENERATED_BODY()
	
public:
	ALightObject();

	// Flicker Function
	UFUNCTION(BlueprintCallable, Category = "Light | Function")
	void ActivateFlickerConstantCycle();
	UFUNCTION(BlueprintCallable, Category = "Light | Function")
	void ActivateFlickerSinCycle();
	UFUNCTION(BlueprintCallable, Category = "Light | Function")
	void ActivateFlickerRandomCycle();
	UFUNCTION(BlueprintCallable, Category = "Light | Function")
	void DeativateFlickerLight();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float deltatTIme) override;

	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	FORCEINLINE float GetConstantCycleIntencity(){ 
		if (mFlickerTargetTime * 2 < mFlickerElapsedTime) mFlickerElapsedTime = 0;
		if(mFlickerTargetTime>=mFlickerElapsedTime) return FMath::Lerp(mFlickerCurrIntencity, mFlickerTargetIntencity, mFlickerElapsedTime / mFlickerTargetTime);
		return FMath::Lerp(mFlickerTargetIntencity, mFlickerCurrIntencity, (mFlickerElapsedTime- mFlickerTargetTime) / mFlickerTargetTime);
	};
	FORCEINLINE float GetSinCycleIntencity() {
		return mFlickerCurrIntencity + mFlickerTargetIntencity * 0.5f * FMath::Sin(mFlickerElapsedTime / mFlickerTargetTime);
	};
	FORCEINLINE float GeRandomCycleIntencity() {
		if (mFlickerTargetTime < mFlickerElapsedTime) mFlickerTargetTime = FMath::RandRange(mRandCycleMinTime, mRandCycleMaxTime);
		return FMath::Lerp(mFlickerCurrIntencity, mFlickerTargetIntencity, mFlickerElapsedTime / mFlickerTargetTime);
	};
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | PointLight")
	class UPointLightComponent* mPointLight;

	// Flicker Option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mIsFlickerOverlapOnly;	// 오버렙 이벤트만 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mIsOverlapEnter;			// 오버렙 이벤트 중 True:Enter False:Exit 를 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	EFlickerType mFlickerType;		// 플리커타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMinTime;		// 랜덤타입시 랜덤최솟값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMaxTime;		// 랜덤타입시 랜덤최솟값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerElapsedTime;		// 현제 플리커 지속시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetTime;		// 목표 플리커 시간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerCurrIntencity;		// 시작 빛의 세기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetIntencity;	// 목표 빛의 세기
	FlickerAction FlickerBindAction;	// 플리커 함수 델리게이트
};
