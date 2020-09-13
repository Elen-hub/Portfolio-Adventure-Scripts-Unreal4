// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "BaseObject.h"
#include "BGMEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ABGMEvent : public ABaseObject
{
	GENERATED_BODY()
	
public:
	ABGMEvent();
	
protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | BGM")
	EBGM mBGMType;
};
