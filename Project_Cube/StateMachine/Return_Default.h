// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/StateMachine/BaseState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_CUBE_API Return_Default : public BaseState
{
public:
	Return_Default() {};
	virtual void OnStateBegin() override;
	virtual void OnStateStay(float DeltaTime) override;
	virtual void OnStateExit() override;
};
