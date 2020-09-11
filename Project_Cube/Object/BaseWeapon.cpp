// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/StaticMeshComponent.h"

ABaseWeapon::ABaseWeapon()
{
	MaxMagazine = 30.f;
	CurrMagazine = MaxMagazine;
	Damage = 10.f;
	FullAutoSpeed = 0.1f;
	ReloadSpeed = 3.f;
	Recoil = 10.f;
	MaxRecoil = 50.f;
	BulletSpread = 1.f;
}
ABaseWeapon* ABaseWeapon::Init()
{

	return this;
}

void ABaseWeapon::ActivateCollision(bool isActivate)
{
	mMesh->SetSimulatePhysics(isActivate);
	mCollision->SetGenerateOverlapEvents(isActivate);
}

void ABaseWeapon::Reload(float magazine)
{
}
