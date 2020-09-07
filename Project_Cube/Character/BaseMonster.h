// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/User.h"
#include "CoreMinimal.h"
#include "Project_Cube/Character/BaseCharacter.h"
#include "BaseMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ABaseMonster : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseMonster();
protected:
	TMap <ECharacterState, class BaseState*> FunctionToStateMap;
	class AAIController* mAIController;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
	virtual void OnAgroCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetCharacterState(const ECharacterState nextState) override;
};
