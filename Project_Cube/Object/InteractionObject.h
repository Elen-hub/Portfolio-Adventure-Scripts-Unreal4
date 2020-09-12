// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "InteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AInteractionObject : public ABaseObject
{
	GENERATED_BODY()
	
public:
	AInteractionObject();
	virtual void Tick(float deltatTime) override;
	FString const* GetInteractionExplanation() { return &mInteractionExplanation; };
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Collision")
	class UPrimitiveComponent* mInteractionCollision;			// Trace에 충돌할 인터렉션 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event | Collision")
	FString mInteractionExplanation;
};
