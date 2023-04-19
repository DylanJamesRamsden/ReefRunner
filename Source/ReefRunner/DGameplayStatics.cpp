// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayStatics.h"

#include "GameFramework/GameMode.h"

ADGameplayGameMode* UDGameplayStatics::GetDGameplayGameMode(const UObject* WorldContext)
{
	if (AGameModeBase* GameMode = GetGameMode(WorldContext))
	{
		if (ADGameplayGameMode* DGameMode = Cast<ADGameplayGameMode>(GameMode))
		{
			return DGameMode;
		}
	}

	return nullptr;
}

ADGameplayGameState* UDGameplayStatics::GetDGameplayGameState(const UObject* WorldContext)
{
	if (AGameStateBase* GameState = GetGameState(WorldContext))
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			return DGameState;
		}
	}

	return nullptr;
}
