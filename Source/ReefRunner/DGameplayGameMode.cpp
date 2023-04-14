// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameMode.h"

#include "DGameplayGameState.h"
#include "Kismet/GameplayStatics.h"

void ADGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AGameStateBase* GS = UGameplayStatics::GetGameState(GetWorld()))
	{
		if (ADGameplayGameState* DGS = Cast<ADGameplayGameState>(GS))
		{
			MyGameState = DGS;
			MyGameState->SetNextGameplayState();
		}
		else UE_LOG(LogTemp, Warning, TEXT("Not using DGameplayGameState!"));
	}
	else UE_LOG(LogTemp, Error, TEXT("No GameState found! This has to be a timing issue!"));
}

void ADGameplayGameMode::StartGame() const
{
	if (MyGameState)
	{
		MyGameState->SetGameplayState(Started);
	}
}
