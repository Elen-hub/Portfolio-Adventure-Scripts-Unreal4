// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase_Forever.h"

void Chase_Forever::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(false);
}

void Chase_Forever::OnStateStay(float deltaTime)
{
	float velocity = mCharacter->GetVelocity().Size();
	mStepSoundElapsedTime += velocity * deltaTime;
	if (mStepSoundElapsedTime > mCharacter->GetStepSoundTargetTime())
	{
		mStepSoundElapsedTime = 0;
		mCharacter->PlaySound(ECharacterSoundType::Move);
	}

	float testDistance = 15.f;
	FAIMoveRequest moveRequest;
	moveRequest.SetGoalActor(mCharacter->GetTarget());
	moveRequest.SetAcceptanceRadius(testDistance);

	FNavPathSharedPtr navPath;
	mAIController->MoveTo(moveRequest, &navPath);
	if (mAIController->GetMoveStatus() == EPathFollowingStatus::Idle)
		mCharacter->Destroy();
}

void Chase_Forever::OnStateExit()
{

}
