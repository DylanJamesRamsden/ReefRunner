// Fill out your copyright notice in the Description page of Project Settings.


#include "DMovingObstacle.h"

#include "DGameplayGameState.h"
#include "Kismet/GameplayStatics.h"

void ADMovingObstacle::BeginPlay()
{
	Super::BeginPlay();

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld()))
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			// Binds to the gameplay state change in DGameplayGameState
			DGameState->OnGameplayStateChanged.AddDynamic(this, &ADMovingObstacle::OnGameplayStateChanged);

			// If the game has already started, just set the actor to tick
			if (DGameState->GetCurrentGameplayState() == Started)
			{
				SetActorTickEnabled(true);
			}
		}
	}
}

void ADMovingObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(GetActorLocation() + (MovementDirection * MovementSpeed));
}

void ADMovingObstacle::OnGameplayStateChanged(EGameplayState NewState)
{
	switch (NewState)
	{
		case Started:
			SetActorTickEnabled(true);
			break;
	}
}
