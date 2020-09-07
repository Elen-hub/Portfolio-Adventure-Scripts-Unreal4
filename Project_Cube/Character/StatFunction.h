// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stat.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatFunction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_CUBE_API UStatFunction : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatFunction();

private:
	FCharacterInformation* mInformation;
	FCombatStat* mBasicStat;
	float mCurrHP;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	UStatFunction* Init(FCharacterInformation* info, FCombatStat* baseStat);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FCharacterInformation* GetInformation();
	FCombatStat* GetStat();
	FORCEINLINE float CurrHP() { return mCurrHP; }
};
