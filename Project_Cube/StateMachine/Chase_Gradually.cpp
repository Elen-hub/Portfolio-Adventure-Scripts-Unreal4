// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase_Gradually.h"

Chase_Gradually::Chase_Gradually(float maxSpeedDistanceTime, bool useSquare)
{
	mbUseSquare = useSquare;
	mMaxSpeedTargetTime = maxSpeedDistanceTime;
	if (mMaxSpeedTargetTime == 0)
		mMaxSpeedTargetTime = 1.f;
}
void Chase_Gradually::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(false);
	mMaxSpeedElasedTime = 0.f;
	mSpeed = mCharacter->TSpeed;
}

void Chase_Gradually::OnStateStay(float deltaTime)
{
	mMaxSpeedElasedTime += deltaTime;
	float per = PERCENT(mMaxSpeedElasedTime, mMaxSpeedTargetTime);
	if (mbUseSquare)
		per *= per;

	float velocity = mCharacter->GetVelocity().Size();
	mStepSoundElapsedTime += velocity * deltaTime;
	if (mStepSoundElapsedTime > mCharacter->GetStepSoundTargetTime())
	{
		mStepSoundElapsedTime = 0;
		mCharacter->PlaySound(ECharacterSoundType::Move);
	}

	mCharacter->TSpeed = FMath::Lerp(0.f, mSpeed ,per);

	FAIMoveRequest moveRequest;
	moveRequest.SetGoalActor(mCharacter->GetTarget());
	moveRequest.SetAcceptanceRadius(10.f);

	FNavPathSharedPtr navPath;
	mAIController->MoveTo(moveRequest, &navPath);
}

void Chase_Gradually::OnStateExit()
{

}