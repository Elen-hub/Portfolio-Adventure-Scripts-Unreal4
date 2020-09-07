// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatFunction.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mStatFunction = CreateDefaultSubobject<UStatFunction>(TEXT("Stat"));

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

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

	TInputVector = FVector(0.f);
}
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	TestInitPos = GetActorLocation();
}
void ABaseCharacter::SetCharacterState(const ECharacterState nextState)
{

}
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ð� ����
	if (mbIsHit) mHitElapsedTime += DeltaTime;

	// �̵��ӵ� ����
	GetCharacterMovement()->MaxWalkSpeed = TSpeed;
	// mFunctionToStateMap[mCharacterState]->OnStateStay;
}

void ABaseCharacter::SetDamage(float damage, float hitTime)
{

}

void ABaseCharacter::SetHitTime(float hitTime)
{
	// �������� �����ð��� ������ �ð����� ��ٸ� ����
	if (mbIsHit && hitTime > mHitTargetTime - mHitElapsedTime)
		return;

	mHitTargetTime = hitTime;
	mbIsHit = true;
}

void ABaseCharacter::SetNuckback(float force)
{

}
