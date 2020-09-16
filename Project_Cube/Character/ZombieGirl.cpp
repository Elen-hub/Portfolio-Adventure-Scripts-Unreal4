// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieGirl.h"
#include "Components/AudioComponent.h"
#include "Project_Cube/StateMachine/Idle_Default.h"
#include "Project_Cube/StateMachine/Chase_Forever.h"
#include "Project_Cube/StateMachine/Return_Default.h"
#include "BaseHero.h"

AZombieGirl::AZombieGirl()
{
	mAgroAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AgroAudio"));
	mAgroAudioComponent->SetupAttachment(GetRootComponent());
	mAgroRange = 0.f;
}

void AZombieGirl::BeginPlay()
{
	Super::BeginPlay();

	Idle_Default* idleState = new Idle_Default();
	idleState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Idle, idleState);
	Chase_Forever* chaseState = new Chase_Forever();
	chaseState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Chase, chaseState);

	mCrySound->bLooping = true;
}

void AZombieGirl::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (mCharacterState == ECharacterState::ECS_Idle)
	{
		if(!mAgroAudioComponent->IsPlaying())
		{
			mAgroAudioComponent->SetSound(mCrySound);
			mAgroAudioComponent->Play();
		}
		// 어그로증감
		if (mTarget != nullptr)
		{
			float velocitySquere = FMath::Square(mTarget->GetVelocity().Size() * deltaTime);
			float radiusCoefficient =	(1.f - (FVector::Distance(GetActorLocation(), mTarget->GetActorLocation()) / (mOverlapCollision->GetScaledSphereRadius()) * 1.1f)) * 0.15f;

			if (mAgroRange <= 0.6f && mAudioComponent->Sound != mCrySound)
			{
				mAgroAudioComponent->SetSound(mCrySound);
				mAgroAudioComponent->Play();
			}
			if (mAgroRange > 0.6f && mAudioComponent->Sound != mAgroSound)
			{
				mAgroAudioComponent->SetSound(mAgroSound);
				mAgroAudioComponent->Play();
			}
			if(mAudioComponent->Sound == mCrySound)
				mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume() * (1-mAgroRange));
			else
				mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume() * mAgroRange);

			mAgroRange = FMath::Clamp(mAgroRange + (velocitySquere * radiusCoefficient + radiusCoefficient) * deltaTime, 0.f, 1.f);
		}
		if (mAgroRange >= 1)
		{
			mAgroAudioComponent->SetSound(mChaseStartSound);
			mAgroAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
			mAgroAudioComponent->Play();
			SetCharacterState(ECharacterState::ECS_Chase);
		}
	}
}
void AZombieGirl::OnAgroCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseHero* character = Cast<ABaseHero>(OtherActor))
		mTarget = character;
}