// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionObject.h"
#include "InteractionDoor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AInteractionDoor : public AInteractionObject
{
	GENERATED_BODY()
	
public:
	AInteractionDoor();
	virtual FText const GetInteractionExplanation() override;
	virtual void Interaction() override;
	virtual void Open();
	virtual void Close();
	virtual void Tick(float deltaTime) override;
protected:
	virtual void BeginPlay() override;
protected:
	// 열려있음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | State")
	bool mIsOpen;								
	// 잠금장치가 설정되어있음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | State")
	bool mIsLocked;									
	// 열려있을때 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | State")
	FRotator mOpenRot;							
	// 닫혀있을때 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | State")
	FRotator mCloseRot;							
	// 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | State")
	float mRotatorTime;						
	// 열때 실행되는 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | Sound")
	class USoundWave* mOpenSound;		
	// 닫힐때 실행되는 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | Sound")
	class USoundWave* mCloseSound;		
	// 잠긴문을 열려고할때 실행되는 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | Sound")
	class USoundWave* mOpenLockDoorSound;
	// 열쇠를 사용할때 실행되는 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | Sound")
	class USoundWave* mUseKeySound;		
	// 문을 열때 필요한 키핸들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | Key")
	int mKeyHandle;							
	// 문을 열면 부셔짐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | Key")
	bool mIsBrokenKey;	
private:
	float mRotatorElapsedTime;
};
