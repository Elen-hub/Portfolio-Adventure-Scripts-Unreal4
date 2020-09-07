// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/StaticMeshComponent.h"

ABaseWeapon::ABaseWeapon()
{

}
ABaseWeapon* ABaseWeapon::Init()
{

	return this;
}

void ABaseWeapon::ActivateCollision(bool isActivate)
{
	mMesh->SetSimulatePhysics(isActivate);
	mCollision->SetGenerateOverlapEvents(isActivate);
	if(isActivate)
		mMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	else
		mMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ABaseWeapon::Equip()
{

}
void ABaseWeapon::Unequip()
{

}

void ABaseWeapon::Reload(float magazine)
{
}
