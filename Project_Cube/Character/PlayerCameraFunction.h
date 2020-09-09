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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPlayerCameraFunction* Init(class USpringArmComponent* springArm, class UCameraComponent* camera);
	void Set(class ABaseCharacter* character, class UMainGameInstance* gameInstance);
	void SetRebound(const float pitch, const float yaw);
	void CameraMoveSide(float axis);
	void CameraMoveUp(float axis);
	void CameraLook(float rate);
	class AItem* GetItemLookCrosshair();

	FORCEINLINE FVector GetMuzzlePos();
	FORCEINLINE FVector GetMuzzleRot();

protected:
	UPROPERTY(EditAnywhere, Category = "PlayerCamera")
	UCameraComponent* mCamera;
	UPROPERTY(EditAnywhere, Category = "SpringArm")
	USpringArmComponent* mCameraSpringArm;
	UPROPERTY()
	UMainGameInstance* mMainGameInstance;
private:
	ABaseCharacter* mTargetCharacter;
	float TMouseAxis;

};
