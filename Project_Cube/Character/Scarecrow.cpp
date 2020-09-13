// Fill out your copyright notice in the Description page of Project Settings.


#include "Scarecrow.h"
#include "Components/AudioComponent.h"
#include "Project_Cube/StateMachine/Idle_Default.h"
#include "Project_Cube/StateMachine/Chase_Look.h"

AScarecrow::AScarecrow()
{

}

void AScarecrow::BeginPlay()
{
	Super::BeginPlay();

	mOverlapCollision->OnComponentEndOverlap.AddDynamic(this, &AScarecrow::OnAgroCollisionExit);

	Idle_Default* idleState = new Idle_Default();
	idleState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Idle, idleState);
	Chase_Look* chaseState = new Chase_Look();
	chaseState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Chase, chaseState);

	mRotatorSound->bLooping = true;
	mAudioComponent->SetSound(mRotatorSound);
}

void AScarecrow::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (mCharacterState == ECharacterState::ECS_Chase)
	{
		if (!Lib::IsPrimitiveComponentRenderedRecently(GetMesh(), 0.2f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Com"));
			mAudioComponent->VolumeMultiplier = Main->SoundMng->GetSFXVolume();
			if(!mAudioComponent->IsPlaying())
				mAudioComponent->Play();

			FunctionToStateMap[mCharacterState]->OnStateStay();
		}
		else
		{
			mAudioComponent->Stop();
		}
	}
	else
	{
		mAudioComponent->Stop();
		FunctionToStateMap[mCharacterState]->OnStateStay();
	}
}

void AScarecrow::OnAgroCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 플레이어가 범위를 나갈경우 Idle
	if (ABaseHero* character = Cast<ABaseHero>(OtherActor))
	{
		mTarget = nullptr;
		SetCharacterState(ECharacterState::ECS_Idle);
	}
}