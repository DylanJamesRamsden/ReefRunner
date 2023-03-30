// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DGameplayGameState.generated.h"

UENUM()
enum EGameplayState
{
	None,
	Generating,
	WaitingToStart,
	Started,
	Ended
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayStateChanged, EGameplayState, NewState);

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADGameplayGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	EGameplayState GameplayState = None;

public:

	FOnGameplayStateChanged OnGameplayStateChanged;

	void SetNextGameplayState();

	EGameplayState GetCurrentGameplayState() const;
};
