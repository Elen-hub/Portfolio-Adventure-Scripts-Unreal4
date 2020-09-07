// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCameraFunction.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_CUBE_API UPlayerCameraFunction : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerCameraFunction();
private:
	class ABaseCharacter* mTargetCharacter;
	float TMouseAxis;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCamera")
	class UCameraComponent* mCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm")
	class USpringArmComponent* mCameraSpringArm;
	UPROPERTY()
	class UMainGameInstance* mMainGameInstance;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPlayerCameraFunction* Init(USpringArmComponent* springArm, UCameraComponent* camera);
	void Set(ABaseCharacter* character, UMainGameInstance* gameInstance);
	void SetRebound(const float pitch, const float yaw);
	void CameraMoveSide(float axis);
	void CameraMoveUp(float axis);
	void CameraLook(float rate);
	class AItem* GetItemLookCrosshair();
};
