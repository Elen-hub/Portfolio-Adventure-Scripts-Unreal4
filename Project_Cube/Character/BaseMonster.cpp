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

	// 오버랩콜리전 몬스터설정 (이벤트만사용, 타입은 월드다이나믹, 충돌관계는 폰과 겹칠때만)
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
	// 콜리전 바인딩
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

	// 몬스터는 상태이동시 이전 상태 Exit 함수 호출 후 다음 상태 Begin 함수 호출
	FunctionToStateMap[mCharacterState]->OnStateExit();
	mCharacterState = nextState;
	FunctionToStateMap[mCharacterState]->OnStateBegin();

}
void ABaseMonster::OnAgroCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어와 겹칠경우 타겟설정 후 Chase 상태이동
	if (ABaseHero* character = Cast<ABaseHero>(OtherActor))
	{
		mTarget = character;
		SetCharacterState(ECharacterState::ECS_Chase);
	}
}