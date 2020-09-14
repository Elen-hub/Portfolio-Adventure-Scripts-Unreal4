// Fill out your copyright notice in the Description page of Project Settings.


#include "Spider.h"
#include "Project_Cube/StateMachine/BaseState.h"
#include "Project_Cube/StateMachine/Chase_Melee.h"
#include "Project_Cube/StateMachine/Idle_Default.h"
#include "Project_Cube/StateMachine/Return_Default.h"
#include "Project_Cube/StateMachine/Attack_Melee.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"

ASpider::ASpider()
{
	mLeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftCollision"));
	mLeftWeaponCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("LeftSocket"));
	mLeftWeaponCollision->SetGenerateOverlapEvents(false);
	mLeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mLeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	mLeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mLeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	mRightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightCollision"));
	mRightWeaponCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightSocket"));
	mRightWeaponCollision->SetGenerateOverlapEvents(false);
	mRightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mRightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	mRightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mRightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ASpider::BeginPlay()
{
	Super::BeginPlay();

	mLeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpider::OnAttackCollisionEnter);
	mRightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpider::OnAttackCollisionEnter);

	Idle_Default* idleState = new Idle_Default();
	idleState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Idle, idleState);
	Chase_Melee* chaseState = new Chase_Melee();
	chaseState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Chase, chaseState);
	Return_Default* returnState = new Return_Default();
	returnState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Return, returnState);
	Attack_Melee* attackState = new Attack_Melee();
	attackState->Init(this);
	FunctionToStateMap.Add(ECharacterState::ECS_Combat, attackState);
}

void ASpider::Tick(float deltaTime)
{
	Super::Tick(deltaTime);


}

void ASpider::OnAttackCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (ABaseCharacter* character = Cast<ABaseCharacter>(OtherActor))
	{
		if (mAttackList.Contains(character))
			return;

		mAttackList.Add(character);
		float damageTest = 10.f;
		character->SetDamage(damageTest);
	}
}

void ASpider::SetActiveAttackCollision(const ESpiderAttackCollisionType activateCollisionType)
{
	switch (activateCollisionType)
	{
	case ESpiderAttackCollisionType::All:
		mRightWeaponCollision->SetGenerateOverlapEvents(true);
		mLeftWeaponCollision->SetGenerateOverlapEvents(true);
		break;
	case ESpiderAttackCollisionType::Left:
		mLeftWeaponCollison->SetGenerateOverlapEvents(true);
		mRightWeaponCollison->SetGenerateOverlapEvents(false);
		break;
	case ESpiderAttackCollisionType::Right:
		mLeftWeaponCollison->SetGenerateOverlapEvents(false);
		mRightWeaponCollison->SetGenerateOverlapEvents(true);
		break;
	case ESpiderAttackCollisionType::None:
		mLeftWeaponCollison->SetGenerateOverlapEvents(false);
		mRightWeaponCollison->SetGenerateOverlapEvents(false);
		break;
	default:
		;
	}
}