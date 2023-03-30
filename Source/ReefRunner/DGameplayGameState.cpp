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
}

EGameplayState ADGameplayGameState::GetCurrentGameplayState() const
{
	return GameplayState;
}
