// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "Crawl.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CUBE_API ACrawl : public ABaseMonster
{
	GENERATED_BODY()

public:
	ACrawl();
	virtual void Tick(float deltaTime) override;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnTextureEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* mEventCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Event")
	class UTexture2D* mEventTexture;	
};
