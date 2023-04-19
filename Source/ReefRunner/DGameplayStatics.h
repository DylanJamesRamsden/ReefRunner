// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGameplayGameMode.h"
#include "DGameplayGameState.h"
#include "Kismet/GameplayStatics.h"
#include "DGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class REEFRUNNER_API UDGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

	static ADGameplayGameMode* GetDGameplayGameMode(const UObject* WorldContext);

	static ADGameplayGameState* GetDGameplayGameState(const UObject* WorldContext);
	
};
