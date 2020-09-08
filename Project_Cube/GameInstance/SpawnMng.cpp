// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_Cube/User.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Cube/Character/BaseHero.h"

USpawnMng::USpawnMng()
{

}

USpawnMng* USpawnMng::Init(UMainGameInstance* gameInstance)
{
	mGameInstance = gameInstance;
	return this;
}

UParticleSystemComponent* USpawnMng::SpawnParticle(UParticleSystem* particle, FVector const& spawnPos, float const& particleSize)
{
	if (!mSpawnedParticleMap.Contains(particle))
		mSpawnedParticleMap.Add(particle, new FSpawnParticleHandler());

    UParticleSystemComponent* spawnedParticle = mSpawnedParticleMap[particle]->GetParticle();
    if (spawnedParticle)
    {
        spawnedParticle->SetWorldLocation(spawnPos);
        spawnedParticle->SetWorldScale3D(particleSize * FVector::OneVector);
        spawnedParticle->SetActive(true);
    }
    else
    {
        UParticleSystemComponent* spanwedPraticle = UGameplayStatics::SpawnEmitterAttached(particle, mGameInstance->MainCharacter->GetRootComponent(), FName("instance"), spawnPos, FRotator::ZeroRotator, EAttachLocation::KeepWorldPosition, false);
        // UParticleSystemComponent* spanwedPraticle = UGameplayStatics::SpawnEmitterAtLocation(mGameInstance->GetWorld(), particle, spawnPos, FRotator::ZeroRotator, true);
        spanwedPraticle->SetWorldScale3D(particleSize * FVector::OneVector);
        mSpawnedParticleMap[particle]->ParticleArray.Add(spanwedPraticle);
    }
	return spawnedParticle;
}

UParticleSystemComponent* FSpawnParticleHandler::GetParticle()
{
	for (auto value : ParticleArray)
    	if (!value->IsActive())
    		return value;

    return nullptr;
}

AActor* FSpawnActorHandler::GetActor()
{
    for (auto value : ActorArray)
        if (value->IsHidden())
            return value;

    return nullptr;
}
