// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonster.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "StatFunction.h"
#include "Project_Cube/StateMachine/BaseState.h"

ABaseMonster::ABaseMonster()
{
	APawn* pawn = Cast<APawn>(this);
	pawn->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	pawn->bUseControllerRotationYaw = true;

	// �������ݸ��� ���ͼ��� (�̺�Ʈ�����, Ÿ���� ������̳���, �浹����� ���� ��ĥ����)
	mOverlapCollision->SetSphereRadius(System::AgroDefaultVolumeRange);
	mOverlapCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mOverlapCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mOverlapCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mOverlapCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	mOverlapCollision->SetHiddenInGame(false);
}
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	mAIController = Cast<AAIController>(GetController());
	// �ݸ��� ���ε�
	mOverlapCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAgroCollisionEnter);

	FCharacterInformation* info = new FCharacterInformation();
	FCombatStat* stat = new FCombatStat();
	stat->HP = 20.f;
	stat->SP = 100.f;

	mStatFunction->Init(info, stat);
}
void ABaseMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (auto in = FunctionToStateMap.CreateIterator(); in; ++in)
		delete in.Value();
}
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FunctionToStateMap[mCharacterState]->OnStateStay(DeltaTime);
}
void ABaseMonster::SetCharacterState(const ECharacterState nextState)
{
	if (nextState == mCharacterState)
		return;

	// ���ʹ� �����̵��� ���� ���� Exit �Լ� ȣ�� �� ���� ���� Begin �Լ� ȣ��
	FunctionToStateMap[mCharacterState]->OnStateExit();
	mCharacterState = nextState;
	FunctionToStateMap[mCharacterState]->OnStateBegin();

}
void ABaseMonster::OnAgroCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �÷��̾�� ��ĥ��� Ÿ�ټ��� �� Chase �����̵�
	if (ABaseHero* character = Cast<ABaseHero>(OtherActor))
	{
		mTarget = character;
		SetCharacterState(ECharacterState::ECS_Chase);
	}
}