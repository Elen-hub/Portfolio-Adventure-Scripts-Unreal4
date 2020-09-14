// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Melee.h"

void Attack_Melee::OnStateBegin()
{
	mAIController->StopMovement();
}

void Attack_Melee::OnStateStay(float deltaTime)
{
	if (mCharacter->IsHit() || !mCharacter->IsPossibleAttack())
		return;

	if (FVector::Distance(mCharacter->GetActorLocation(), mCharacter->GetTarget()->GetActorLocation()) > mCharacter->TRange)
	{
		mCharacter->SetCharacterState(ECharacterState::ECS_Chase);
		return;
	}

	mCharacter->ClearAttackList();
	mCharacter->SetActorRotation(Lib::GetLookAtRotator(mCharacter->GetActorLocation(), mCharacter->GetTarget()->GetActorLocation(), mCharacter->GetActorUpVector()));

	mAttackCount = FMath::RandRange(1, 3);
	FString attackSectionName = "Attack";
	attackSectionName.AppendInt(mAttackCount);
	switch (mAttackCount)
	{
	case 0:
		mCharacter->SetAttackTime(1.5f);
		mAnimInstance->Montage_Play(mCharacter->GetCombatMontage(), 2.f);
		mAnimInstance->Montage_JumpToSection(FName(attackSectionName), mCharacter->GetCombatMontage());
		break;
	case 1:
		mCharacter->SetAttackTime(1.5f);
		mAnimInstance->Montage_Play(mCharacter->GetCombatMontage(), 1.5f);
		mAnimInstance->Montage_JumpToSection(FName(attackSectionName), mCharacter->GetCombatMontage());
		break;
	case 2:
		mCharacter->SetAttackTime(1.5f);
		mAnimInstance->Montage_Play(mCharacter->GetCombatMontage(), 1.5f);
		mAnimInstance->Montage_JumpToSection(FName(attackSectionName), mCharacter->GetCombatMontage());
		break;
	default:
		;
	}
}

void Attack_Melee::OnStateExit()
{

}