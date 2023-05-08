// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

enum EGameplayState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	ADPlayerState();

	FVector StartingLocation;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState NewState);
};
