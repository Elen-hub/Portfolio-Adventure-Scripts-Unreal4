// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Melee.h"

void Attack_Melee::OnStateBegin()
{
	mAIController->StopMovement();
	mCharacter->ClearAttackList();
}

void Attack_Melee::OnStateStay()
{
	if (!mCharacter->IsHit() || !mCharacter->IsPossibleAttack())
		return;

	if (FVector::Distance(mCharacter->GetActorLocation(), mCharacter->GetTarget()->GetActorLocation()) > mCharacter->TRange)
	{
		mCharacter->SetCharacterState(ECharacterState::ECS_Chase);
		return;
	}

	mAttackCount = FMath::RandRange(0, 3);

	FName attackSectionName = "Attack" + FMath::RandRange(0, 3);

	mCharacter->SetAttackTime(1.5f);

	switch (mAttackCount)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s , %f"), &attackSectionName, mAttackCount);
}

void Attack_Melee::OnStateExit()
{

}