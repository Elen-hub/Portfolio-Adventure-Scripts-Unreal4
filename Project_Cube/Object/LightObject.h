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
	bool mIsFlickerOverlapOnly;	// ������ �̺�Ʈ�� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mIsOverlapEnter;			// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	EFlickerType mFlickerType;		// �ø�ĿŸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMinTime;		// ����Ÿ�Խ� �����ּڰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMaxTime;		// ����Ÿ�Խ� �����ּڰ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerElapsedTime;		// ���� �ø�Ŀ ���ӽð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetTime;		// ��ǥ �ø�Ŀ �ð�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerCurrIntencity;		// ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetIntencity;	// ��ǥ ���� ����
	FlickerAction FlickerBindAction;	// �ø�Ŀ �Լ� ��������Ʈ
};
