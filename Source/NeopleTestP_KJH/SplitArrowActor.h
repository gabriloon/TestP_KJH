// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArrowActor.h"
#include "SplitArrowActor.generated.h"

/**
 * 
 */
UCLASS()
class NEOPLETESTP_KJH_API ASplitArrowActor : public AArrowActor
{
	GENERATED_BODY()
	
	protected:
	virtual void BeginPlay() override;

	public:
	ASplitArrowActor();

	void SplitFunction();

	FTimerHandle TimerHandle;

	private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorToSpawn;

};
