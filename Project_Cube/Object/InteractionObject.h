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
	virtual FText const GetInteractionExplanation() { return mInteractionExplanation; };
	virtual void Interaction() {};
protected:
	virtual void BeginPlay() override;

protected:
	// Trace에 충돌할 인터렉션 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UPrimitiveComponent* mInteractionCollision;			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText mInteractionExplanation;
};
