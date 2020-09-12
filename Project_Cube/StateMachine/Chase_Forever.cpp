// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase_Forever.h"

void Chase_Forever::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(false);
}

void Chase_Forever::OnStateStay()
{
	float testDistance = 15.f;
	FAIMoveRequest moveRequest;
	moveRequest.SetGoalActor(mCharacter->GetTarget());
	moveRequest.SetAcceptanceRadius(testDistance);

	FNavPathSharedPtr navPath;
	mAIController->MoveTo(moveRequest, &navPath);
}

void Chase_Forever::OnStateExit()
{

}
