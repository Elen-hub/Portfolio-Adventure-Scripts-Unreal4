// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Cube/StateMachine/BaseState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_CUBE_API Chase_Look : public BaseState
{
public:
	Chase_Look() {};
	virtual void OnStateBegin() override;
	virtual void OnStateStay() override;
	virtual void OnStateExit() override;
};
