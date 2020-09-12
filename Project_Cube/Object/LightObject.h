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
	void ActivateFlickerConstantLerp();
	void ActivateFlickerConstants();
	void ActivateFlickerRandomLerp();
	void DeativateFlickerLight();
	void SwitchOn();
	void SwitchOff();

	// Broken Option
	void Broken();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float deltatTIme) override;

	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	float GetConstantIntencity();
	float GetConstantsIntencity();
	float GeRandomIntencity();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | PointLight")
	class UPointLightComponent* mPointLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | PointLight")
	USoundWave* mLightBuzzSound;

	// Siwtch Option
	// 스위치 이벤트 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Switch")
	bool mbUseSwitchEvent;				
	// 스위치 이벤트 중 True:Enter False:Exit (정방향) 을사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Switch")
	bool mbSwitchOverlapEnter;	
	// 목표 빛의 세기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Switch")
	float mSwitchIntencity;			

	// Flicker Option
		// 오버렙 이벤트만 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mbIsFlickerOverlapOnly;	
	// 오버렙 이벤트 중 True:Enter False:Exit 를 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mbFlickerOverlapEnter;	
	// 플리커타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	EFlickerType mFlickerType;		
	// 랜덤타입시 랜덤최솟값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMinTime;			
	// 랜덤타입시 랜덤최솟값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMaxTime;		
	// 상수연속실행값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	TArray<float> mConstantArray;
	// 현제 진행상수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mCurrConstant;				
	// 현제 플리커 지속시간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerElapsedTime;		
	// 목표 플리커 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetTime;		
	// 시작 빛의 세기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerCurrIntencity;		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
		// 목표 빛의 세기
	float mFlickerTargetIntencity;		
	// 플리커 함수 델리게이트
	FlickerAction FlickerBindAction;	
	
	// Broken Option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	bool mbUseBrokenOverlap;			// 오버렙 이벤트시 부셔지는 효과를 받음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	bool mbBrokenOverlapEnter;		// 오버렙 이벤트 중 True:Enter False:Exit 를 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	USoundWave* mBrokenSound;		// 오버렙 이벤트 중 True:Enter False:Exit 를 사용
};
