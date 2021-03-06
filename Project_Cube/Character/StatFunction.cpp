// Fill out your copyright notice in the Description page of Project Settings.


#include "StatFunction.h"

UStatFunction::UStatFunction()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UStatFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UStatFunction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(mInformation) delete mInformation;
	if(mBasicStat) delete mBasicStat;
}
UStatFunction* UStatFunction::Init(FCharacterInformation* info, FCombatStat* baseStat)
{
	mInformation = info;
	mBasicStat = baseStat;
	mCurrHP = GetStat()->HP;
	return this;
}
FCharacterInformation* UStatFunction::GetInformation()
{
	return mInformation;
}
FCombatStat* UStatFunction::GetStat()
{
	return mBasicStat;
}

bool UStatFunction::SetDamage(float damage)
{
	// 체력이 0이하가 된다면 true리턴
	mCurrHP -= damage;
	if (mCurrHP <= 0)
	{
		mCurrHP = 0;
		return true;
	}
	return false;
}

