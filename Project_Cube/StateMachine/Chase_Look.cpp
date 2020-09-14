// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase_Look.h"


void Chase_Look::OnStateBegin()
{

}

void Chase_Look::OnStateStay(float deltaTime)
{
	FRotator lookAtRot = Lib::GetLookAtRotator(mCharacter->GetActorLocation(), mCharacter->GetTarget()->GetActorLocation(), mCharacter->GetActorUpVector());
	mCharacter->SetActorRotation(lookAtRot);
}

void Chase_Look::OnStateExit()
{

}
