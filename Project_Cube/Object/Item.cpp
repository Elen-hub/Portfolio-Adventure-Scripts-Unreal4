// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Project_Cube/UI/MainUI.h"
#include "Project_Cube/Character/BaseHero.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AItem::AItem()
{
	Name = "TestItem";
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Event Collision"));
	mCollision->SetupAttachment(GetRootComponent());
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// 메쉬 설정 (이벤트만사용, 타입은 월드다이나믹, 충돌관계는 폰과 겹칠때만)
	mMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	mMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	mMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	mMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	
	USphereComponent* sphere = Cast<USphereComponent>(mCollision);
	sphere->InitSphereRadius(System::ItemDefaultVolumeRange);
}
AItem* AItem::Init()
{
	return this;
}
void AItem::GetItem()
{
	mMesh->SetSimulatePhysics(false);
	mCollision->SetGenerateOverlapEvents(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}
FText AItem::GetItemSelectText()
{
	FText refValue;
	switch (mItemType)
	{
	case EItemType::EIT_AssaultRifle:
	case EItemType::EIT_Pistol:
	case EItemType::EIT_Shotgun:
		refValue = FText::FromString("[Weapon]Equip to " + Name);
		break;

	case EItemType::EIT_Bullet:
	case EItemType::EIT_Potion:
	case EItemType::EIT_Other:
		refValue = FText::FromString("[Item]Get " + Name);
		break;

	default:
		;
	}
	return refValue;
}