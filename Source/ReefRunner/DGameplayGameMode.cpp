// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameMode.h"

#include "DGameplayGameState.h"
#include "Kismet/GameplayStatics.h"

void ADGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADGameplayGameMode::StartGame() const
{
	if (GameState)
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->SetGameplayState(Started);
		}
	}
}

void ADGameplayGameMode::NextLevel() const
{
	if (GameState)
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->SetNextLevel();	
		}
	}
}

void ADGameplayGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);

	if (GameState)
	{
		// Starts the world generation next tick (this ensures everything that needs be is bound to OnGameplayStateChanged)
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			GetWorldTimerManager().SetTimerForNextTick(DGameState, &ADGameplayGameState::SetNextGameplayState);
		}
	}
}
