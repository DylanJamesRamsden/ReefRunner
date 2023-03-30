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

	UPROPERTY()
	ADGameplayGameState* MyGameState;

	virtual void BeginPlay() override;
};
