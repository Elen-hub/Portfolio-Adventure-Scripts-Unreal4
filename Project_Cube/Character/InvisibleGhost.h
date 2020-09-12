// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "InvisibleGhost.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API AInvisibleGhost : public ABaseMonster
{
	GENERATED_BODY()

public:
	AInvisibleGhost::AInvisibleGhost();

protected:
	virtual void BeginPlay() override;
};
