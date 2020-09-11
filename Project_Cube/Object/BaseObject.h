// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObject.generated.h"

UCLASS()
class PROJECT_CUBE_API ABaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObject();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Mesh")
	class UStaticMeshComponent* mMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Collision")
	class UPrimitiveComponent* mCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Sound")
	class UAudioComponent* mAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Delay")
	bool mbUseDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Delay")
	float mDelayTime;

	FTimerHandle mDelayTimer;
protected:
	virtual void BeginPlay() override;
	template< class T >
	void SetDelayTimer(T* inObj, void (T::* inMethod)());
	UFUNCTION()
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};
	UFUNCTION()
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {};
public:	
	virtual void Tick(float DeltaTime) override;
};
