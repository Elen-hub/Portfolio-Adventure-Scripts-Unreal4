// Fill out your copyright notice in the Description page of Project Settings.


#include "Return_Default.h"

void Return_Default::OnStateBegin()
{
	mCharacter->SetTarget(nullptr);
}

void Return_Default::OnStateStay(float deltaTime)
{
	FAIMoveRequest moveRequest;
	moveRequest.SetGoalLocation(mCharacter->TestInitPos);
	moveRequest.SetAcceptanceRadius(0.1f);

	FNavPathSharedPtr navPath;
	mAIController->MoveTo(moveRequest, &navPath);

	if (mAIController->GetMoveStatus() == EPathFollowingStatus::Idle)
		mCharacter->SetCharacterState(ECharacterState::ECS_Idle);
}

void Return_Default::OnStateExit()
{

}
