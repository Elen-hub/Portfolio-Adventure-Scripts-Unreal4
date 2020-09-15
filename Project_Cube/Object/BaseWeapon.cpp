// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

ABaseWeapon::ABaseWeapon()
{
	FStringClassReference classRef("Blueprint'/Game/TestContent/Bullet_BP.Bullet_BP_C'");
	mBulletRefClass = classRef.TryLoadClass<AActor>();

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
	if (isActivate)
	{

	}
	else
	{
		if (mGetSound)
		{
			if (mAudioComponent->Sound != mGetSound)
				mAudioComponent->SetSound(mGetSound);

			mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
			mAudioComponent->Play();
		}
	}
	mMesh->SetSimulatePhysics(isActivate);
	mCollision->SetGenerateOverlapEvents(isActivate);
}

void ABaseWeapon::Fire(FVector muzzleLocation, FVector direction)
{
	// ÃÑ¾Ë¹ß»ç
	ABullet* bullet = GetGameInstance<UMainGameInstance>()->SpawnMng->SpawnActor<ABullet>(mBulletRefClass);
	bullet->Enabled(muzzleLocation, direction, 0, Damage, 0.1f);
	CurrMagazine -= 1;

	if (mFireSound)
	{
		if (mAudioComponent->Sound != mFireSound)
			mAudioComponent->SetSound(mFireSound);

		mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
		mAudioComponent->Play();
	}
}

void ABaseWeapon::PlayReloadSound()
{
	if (mReloadSound)
	{
		if (mAudioComponent->Sound != mReloadSound)
			mAudioComponent->SetSound(mReloadSound);

		mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
		mAudioComponent->Play();
	}
}

void ABaseWeapon::PlayEmptyShotSound()
{
	if (mEmptyShotSound)
	{
		if (mAudioComponent->Sound != mEmptyShotSound)
			mAudioComponent->SetSound(mEmptyShotSound);

		mAudioComponent->SetVolumeMultiplier(Main->SoundMng->GetSFXVolume());
		mAudioComponent->Play();
	}
}
