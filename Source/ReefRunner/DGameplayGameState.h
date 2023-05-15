// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DGameplayGameState.generated.h"

UENUM(BlueprintType)
enum EGameplayState
{
	None,
	Generating,
	WaitingToStart,
	Started,
	Ended
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayStateChanged, EGameplayState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int32, NewLevel);

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADGameplayGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	EGameplayState GameplayState = None;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxLevels = 3;

	int32 Level = 1;

public:

	FOnGameplayStateChanged OnGameplayStateChanged;

	// Sets the gameplay state to the specified gameplay state
	void SetGameplayState(EGameplayState NewState);

	UFUNCTION(BlueprintCallable)
	EGameplayState GetCurrentGameplayState() const;

	FOnLevelChanged OnLevelChanged;;
	
	void SetNextLevel();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevel() const;

	int32 GetMaxLevels() const;
};
