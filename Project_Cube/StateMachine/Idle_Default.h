// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_CUBE_API Idle_Default : public BaseState
{
public:
	Idle_Default() {}
	virtual void OnStateBegin() override;
	virtual void OnStateStay() override;
	virtual void OnStateExit() override;;
};
