// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_CUBE_API Idle_Wait : public BaseState
{
public:
	Idle_Wait() {}
	virtual void OnStateBegin() override;
	virtual void OnStateStay(float DeltaTime) override;
	virtual void OnStateExit() override;;
};
