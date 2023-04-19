// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameplayGameMode.generated.h"

class ADGameplayGameState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	// Starts the game. Sets the gameplay state to 'Started'
	UFUNCTION(Exec)
	void StartGame() const;

	// Starts the game. Sets the gameplay state to 'Started'
	UFUNCTION(Exec)
	void NextLevel() const;

	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;

public:

	void OnGenerationComplete() const;
};
