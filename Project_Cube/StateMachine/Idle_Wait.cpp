// Fill out your copyright notice in the Description page of Project Settings.


#include "Idle_Wait.h"

Idle_Wait::Idle_Wait(float radiusPerFrame)
{
	mRadiusPerFrame = radiusPerFrame;
}

void Idle_Wait::OnStateBegin()
{
	mCharacter->GetOverlapCollision()->SetGenerateOverlapEvents(true);
	mCharacter->PlaySound(ECharacterSoundType::Idle);
}

void Idle_Wait::OnStateStay(float deltaTime)
{
	mCharacter->GetOverlapCollision()->SetSphereRadius(mCharacter->GetOverlapCollision()->GetScaledSphereRadius() + mRadiusPerFrame);
}

void Idle_Wait::OnStateExit()
{

}