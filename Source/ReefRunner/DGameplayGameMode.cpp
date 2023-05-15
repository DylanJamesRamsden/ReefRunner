// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameMode.h"

#include "DGameplayGameState.h"
#include "DGameplayStatics.h"

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

	GetWorldTimerManager().SetTimerForNextTick(this, &ADGameplayGameMode::StartGeneration);
}

void ADGameplayGameMode::StartGeneration() const
{
	if (GameState)
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->SetGameplayState(Generating);
		}
	}
}

void ADGameplayGameMode::OnGenerationComplete() const
{
	if (GameState)
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->SetGameplayState(WaitingToStart);
		}
	}
}

void ADGameplayGameMode::OnStartInitiated() const
{
	if (GameState)
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->SetGameplayState(Started);
		}
	}
}

void ADGameplayGameMode::OnGameComplete() const
{
	if (GameState)
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->SetGameplayState(Ended);
		}
	}
}

void ADGameplayGameMode::RestartGame()
{
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	UDGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName);
}
