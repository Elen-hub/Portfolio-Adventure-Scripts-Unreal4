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
	// ����ġ �̺�Ʈ ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Switch")
	bool mbUseSwitchEvent;				
	// ����ġ �̺�Ʈ �� True:Enter False:Exit (������) �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Switch")
	bool mbSwitchOverlapEnter;	
	// ��ǥ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Switch")
	float mSwitchIntencity;			

	// Flicker Option
		// ������ �̺�Ʈ�� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mbIsFlickerOverlapOnly;	
	// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mbFlickerOverlapEnter;	
	// �ø�ĿŸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	EFlickerType mFlickerType;		
	// ����Ÿ�Խ� �����ּڰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMinTime;			
	// ����Ÿ�Խ� �����ּڰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMaxTime;		
	// ������ӽ��ప
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	TArray<float> mConstantArray;
	// ���� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mCurrConstant;				
	// ���� �ø�Ŀ ���ӽð�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerElapsedTime;		
	// ��ǥ �ø�Ŀ �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetTime;		
	// ���� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerCurrIntencity;		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
		// ��ǥ ���� ����
	float mFlickerTargetIntencity;		
	// �ø�Ŀ �Լ� ��������Ʈ
	FlickerAction FlickerBindAction;	
	
	// Broken Option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	bool mbUseBrokenOverlap;			// ������ �̺�Ʈ�� �μ����� ȿ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	bool mbBrokenOverlapEnter;		// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	USoundWave* mBrokenSound;		// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
};
