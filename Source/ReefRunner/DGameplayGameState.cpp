// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameState.h"

void ADGameplayGameState::SetNextGameplayState()
{
	switch (GameplayState)
	{
		case None:
			GameplayState = Generating;
			break;
		case Generating:
			GameplayState = WaitingToStart;
			break;
		case WaitingToStart:
			GameplayState = Started;
			break;
		case Started:
			GameplayState = Ended;
			break;
		case Ended:
			break;
	}

	OnGameplayStateChanged.Broadcast(GameplayState);

	UE_LOG(LogTemp, Log, TEXT("GameplayState changed, new state: %s"), *UEnum::GetValueAsString(GameplayState));
}

void ADGameplayGameState::SetGameplayState(EGameplayState NewState)
{
	GameplayState = NewState;

	OnGameplayStateChanged.Broadcast(NewState);
}

EGameplayState ADGameplayGameState::GetCurrentGameplayState() const
{
	return GameplayState;
}

void ADGameplayGameState::SetNextLevel()
{
	if (Level == MaxLevels)
	{
		Level = 1;
	}
	else Level++;

	UE_LOG(LogTemp, Log, TEXT("Level changed, new level: %d"), Level);

	OnLevelChanged.Broadcast(Level);
}

int32 ADGameplayGameState::GetCurrentLevel() const
{
	return Level;
}

int32 ADGameplayGameState::GetMaxLevels() const
{
	return MaxLevels;
}
