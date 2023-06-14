// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerState.h"

#include "DCharacter.h"
#include "DGameplayGameState.h"
#include "DGameplayStatics.h"

ADPlayerState::ADPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
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
		// Dividing by 100 to ensure the score is based on meters
		SetScore((PlayerPawn->GetActorLocation().X - StartingLocation.X) / 100.0f);
	}

	if (GetScore() >=  LevelChangeScore)
	{
		if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
		{
			DGameState->SetNextLevel();

			if (ADCharacter* DCharacter = Cast<ADCharacter>(GetPawn()))
			{
				// @TODO Change this method up a bit, isn't the most accurate way to scale level change with speed
				LevelChangeScore += 100.0f + (100 * (int)(DCharacter->GetCurrentSpeed() / 1.0f));
			}
		}
	}
}

void ADPlayerState::OnGameplayStateChanged(EGameplayState NewState)
{
	if (NewState == Started)
	{
		SetActorTickEnabled(true);

		Oxygen = OxygenStartingAmount;

		GetWorldTimerManager().SetTimer(OxygenDecreaseTimerHandle, this, &ADPlayerState::DecreaseOxygen, OxygenDecreaseTime, true);
	}
	else if (NewState == Ended)
	{
		GetWorldTimerManager().ClearTimer(OxygenDecreaseTimerHandle);
	}
}

void ADPlayerState::DecreaseOxygen()
{
	Oxygen = FMath::Clamp(Oxygen - OxygenDecreaseAmount, 0, OxygenStartingAmount);
}

float ADPlayerState::GetLevelChangeScore()
{
	return LevelChangeScore;
}

float ADPlayerState::GetOxygen()
{
	return Oxygen;
}

void ADPlayerState::AddOxygen(float Amount)
{
	Oxygen += Amount;
}
