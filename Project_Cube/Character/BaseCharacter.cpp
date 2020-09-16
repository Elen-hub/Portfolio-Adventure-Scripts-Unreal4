// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatFunction.h"
#include "Components/AudioComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mStatFunction = CreateDefaultSubobject<UStatFunction>(TEXT("Stat"));

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	mAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Character Sound"));
	mAudioComponent->SetupAttachment(GetRootComponent());

	// �������ݸ��� �⺻���� ( �浹�̺�Ʈ ������, �浹���� ��� ���� )
	mOverlapCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Collision"));
	mOverlapCollision->SetupAttachment(GetRootComponent());
	mOverlapCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mOverlapCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	mOverlapCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// ĳ���Ͱ� ������ �������� ������ ����
	GetCharacterMovement()->bOrientRotationToMovement = false;
	// Yaw 540�ӵ��� ȸ��
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	// ���� ��
	GetCharacterMovement()->JumpZVelocity = 500.f;
	// ������Ʈ��
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxAcceleration = 500.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 50.f;

	mStepSoundTargetTime = 100.f;
	mHitParticleSize = 1.f;
	TInputVector = FVector(0.f);
}
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	mCharacterSoundMap.Add(ECharacterSoundType::Idle, mIdleSound);
	mCharacterSoundMap.Add(ECharacterSoundType::Move, mMoveSound);
	mCharacterSoundMap.Add(ECharacterSoundType::Hit, mHitSound);
	mCharacterSoundMap.Add(ECharacterSoundType::Death, mDeathSound);

	mAnimInstance = GetMesh()->GetAnimInstance();
	TestInitPos = GetActorLocation();
}
void ABaseCharacter::SetCharacterState(const ECharacterState nextState)
{
	mCharacterState = nextState;
}
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ð� ����
	if (mbIsHit) mHitElapsedTime += DeltaTime;
	// ���ݽð� ����
	if (mAttackElapsedTime >0)	mAttackElapsedTime -= DeltaTime;
	// �̵��ӵ� ����
	GetCharacterMovement()->MaxWalkSpeed = TSpeed;
	// mFunctionToStateMap[mCharacterState]->OnStateStay;
}

void ABaseCharacter::SetDamage(float damage)
{
	if (mCharacterState == ECharacterState::ECS_Death)
		return;

	if (mStatFunction->SetDamage(damage))
		SetCharacterState(ECharacterState::ECS_Death);
}

void ABaseCharacter::SetHitTime(float hitTime)
{
	// �������� �����ð��� ������ �ð����� ��ٸ� ����
	if (mbIsHit && hitTime > mHitTargetTime - mHitElapsedTime)
		return;

	mHitTargetTime = hitTime;
	mbIsHit = true;
}

void ABaseCharacter::SetHitEffect(FVector hitPoint, FVector directionVector)
{
	Main->SpawnMng->SpawnParticle(mHitParticle, hitPoint, directionVector.Rotation(), mHitParticleSize);
}

void ABaseCharacter::SetNuckback(FVector direction, float force)
{
	GetCharacterMovement()->AddImpulse(direction * force* 1000.f);
}

void ABaseCharacter::Death()
{
	mTarget = nullptr;
	GetMesh()->SetGenerateOverlapEvents(false);
	mOverlapCollision->SetGenerateOverlapEvents(false);

	PlaySound(ECharacterSoundType::Death);
}
void ABaseCharacter::WalkStart()
{
	mbIsWalk = true;
}
void ABaseCharacter::WalkEnd()
{
	mbIsWalk = false;
}

void ABaseCharacter::PlaySound(const ECharacterSoundType sound)
{
	if (!mCharacterSoundMap.Contains(sound))
		return;

	if(mAudioComponent->Sound != mCharacterSoundMap[sound])
		mAudioComponent->SetSound(mCharacterSoundMap[sound]);

	mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
	mAudioComponent->Play();
}

void ABaseCharacter::PlaySound(USoundWave* sound)
{
	if (sound == nullptr)
		return;

	if (mAudioComponent->Sound != sound)
		mAudioComponent->SetSound(sound);

	mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
	mAudioComponent->Play();
}

void ABaseCharacter::StopSound()
{
	if(mAudioComponent->IsPlaying())
		mAudioComponent->Stop();
}