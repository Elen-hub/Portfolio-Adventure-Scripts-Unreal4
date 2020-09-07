// Fill out your copyright notice in the Description page of Project Settings.


#include "Idle_Default.h"

void Idle_Default::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(true);
}

void Idle_Default::OnStateStay()
{

}

void Idle_Default::OnStateExit()
{

}