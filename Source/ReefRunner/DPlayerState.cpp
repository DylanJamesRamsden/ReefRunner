// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerState.h"

#include "DGameplayGameState.h"
#include "DGameplayStatics.h"

ADPlayerState::ADPlayerState()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ADPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		// Binds to the gameplay state change in DGameplayGameState
		DGameState->OnGameplayStateChanged.AddDynamic(this, &ADPlayerState::OnGameplayStateChanged);
	}
}

void ADPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Updates the player's score
	if (const APawn* PlayerPawn = GetPawn())
	{
		// Unreal has a built in score system, just using that
		SetScore(PlayerPawn->GetActorLocation().X - StartingLocation.X);
	}
}

void ADPlayerState::OnGameplayStateChanged(EGameplayState NewState)
{
	if (NewState == Started)
	{
		SetActorTickEnabled(true);
	}
}
