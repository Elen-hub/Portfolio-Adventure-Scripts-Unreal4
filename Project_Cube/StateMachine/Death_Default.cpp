// Fill out your copyright notice in the Description page of Project Settings.


#include "Death_Default.h"
#include "GameFramework/CharacterMovementComponent.h"

void Death_Default::OnStateBegin()
{
	mCharacter->Death();
	// �������̾��ٸ� ���ӷ�*0.1��ŭ �̵�
	const FVector finaliyRoot = mCharacter->GetActorLocation() + mCharacter->GetActorForwardVector() * mCharacter->GetCharacterMovement()->MaxWalkSpeed * 0.2f;
	mAIController->MoveToLocation(finaliyRoot);
}

void Death_Default::OnStateStay()
{

}

void Death_Default::OnStateExit()
{

}
