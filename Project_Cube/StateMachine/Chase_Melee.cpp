// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase_Melee.h"
void Chase_Melee::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(false);
}

void Chase_Melee::OnStateStay()
{
	float testDistance = 15.f;
	FAIMoveRequest moveRequest;
	moveRequest.SetGoalActor(mCharacter->GetTarget());
	moveRequest.SetAcceptanceRadius(testDistance);

	FNavPathSharedPtr navPath;
	mAIController->MoveTo(moveRequest, &navPath);
	if (FVector::Distance(mCharacter->GetActorLocation(), mCharacter->GetTarget()->GetActorLocation()) > System::ChaseDefaultMaxDistance)
		mCharacter->SetCharacterState(ECharacterState::ECS_Return);
}

void Chase_Melee::OnStateExit()
{

}
