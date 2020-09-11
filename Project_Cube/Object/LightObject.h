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
	// Flicker Option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mbIsFlickerOverlapOnly;	// ������ �̺�Ʈ�� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	bool mbFlickerOverlapEnter;			// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	EFlickerType mFlickerType;		// �ø�ĿŸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMinTime;		// ����Ÿ�Խ� �����ּڰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mRandCycleMaxTime;		// ����Ÿ�Խ� �����ּڰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	TArray<float> mConstantArray;// ������ӽ��ప
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mCurrConstant;				// ���� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerElapsedTime;		// ���� �ø�Ŀ ���ӽð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetTime;		// ��ǥ �ø�Ŀ �ð�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light | Flicker")
	float mFlickerCurrIntencity;		// ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Flicker")
	float mFlickerTargetIntencity;	// ��ǥ ���� ����
	FlickerAction FlickerBindAction;	// �ø�Ŀ �Լ� ��������Ʈ
	
	// Broken Option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	bool mbUseBrokenOverlap;			// ������ �̺�Ʈ�� �μ����� ȿ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	bool mbBrokenOverlapEnter;		// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light | Broken")
	USoundWave* mBrokenSound;		// ������ �̺�Ʈ �� True:Enter False:Exit �� ���
};
