// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_CUBE_API Chase_Gradually : public BaseState
{
public:
	Chase_Gradually(float maxSpeedDistanceTime, bool useSquare);
	virtual void OnStateBegin() override;
	virtual void OnStateStay(float DeltaTime) override;
	virtual void OnStateExit() override;;

private:

	float mMaxSpeedTargetTime;
	float mMaxSpeedElasedTime;
	bool mbUseSquare;

	float mStepSoundElapsedTime;
	float mSpeed;
};
