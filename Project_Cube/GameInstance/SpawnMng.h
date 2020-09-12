// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpawnMng.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API USpawnMng : public UObject
{
	GENERATED_BODY()
	
public:
	USpawnMng();
	USpawnMng* Init(class UMainGameInstance* gameInstance);
	template <class T = AActor> T* SpawnActor(UClass* refActor, FVector const& location, FRotator const& rotation);
	class UParticleSystemComponent* SpawnParticle(class UParticleSystem* particle, FVector const& spawnPos, float const& particleSize = 1.f);
private:
	TMap<UClass*, FSpawnActorHandler*> mSpawnedActorMap;
	TMap<UParticleSystem*, FSpawnParticleHandler*> mSpawnedParticleMap;
	UMainGameInstance* mGameInstance;
};

template<class T>
T* USpawnMng::SpawnActor(UClass* refActor, FVector const& location = FVector::ZeroVector, FRotator const& rotation = FRotator::ZeroRotator)
{
	if (!mSpawnedActorMap.Contains(refActor))
		mSpawnedActorMap.Add(refActor, new FSpawnActorHandler());

	AActor* spawnActor = mSpawnedActorMap[refActor]->GetActor();
	if (!spawnActor)
	{
		const FActorSpawnParameters spawnParameters;
		spawnActor = mGameInstance->GetWorld()->SpawnActor<AActor>(refActor, location, rotation, spawnParameters);
		mSpawnedActorMap[refActor]->ActorArray.Add(spawnActor);
	}
	return Cast<T>(spawnActor);
}

USTRUCT()
struct FSpawnActorHandler
{
	GENERATED_USTRUCT_BODY()

	TArray<AActor*> ActorArray;
	AActor* GetActor();
};

USTRUCT()
struct FSpawnParticleHandler
{
	GENERATED_USTRUCT_BODY()

	TArray<class UParticleSystemComponent*> ParticleArray;
	UParticleSystemComponent* GetParticle();
};