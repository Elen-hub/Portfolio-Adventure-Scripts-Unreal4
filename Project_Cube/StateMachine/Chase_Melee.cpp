// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase_Melee.h"
void Chase_Melee::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(false);

	mStepSoundElapsedTime = 0;
}

void Chase_Melee::OnStateStay()
{
	float distanceToTarget = FVector::Distance(mCharacter->GetActorLocation(), mCharacter->GetTarget()->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), distanceToTarget, mCharacter->TRange);
	if (distanceToTarget < mCharacter->TRange)
	{
		// State Change (Attack)
		mCharacter->SetCharacterState(ECharacterState::ECS_Combat);
		return;
	}
	else if (distanceToTarget > System::ChaseDefaultMaxDistance)
	{
		// State Change (Chase)
		mCharacter->SetCharacterState(ECharacterState::ECS_Return);
		return;
	}

	float velocity = mCharacter->GetVelocity().Size();
	mStepSoundElapsedTime += velocity;
	if (mStepSoundElapsedTime > mCharacter->GetStepSoundTargetTime())
	{
		mStepSoundElapsedTime = 0;
		mCharacter->PlaySound(ECharacterSoundType::Move);
	}

	FAIMoveRequest moveRequest;
	moveRequest.SetGoalActor(mCharacter->GetTarget());
	moveRequest.SetAcceptanceRadius(mCharacter->TRange *0.3f);
	FNavPathSharedPtr navPath;
	mAIController->MoveTo(moveRequest, &navPath);
}

void Chase_Melee::OnStateExit()
{

}
