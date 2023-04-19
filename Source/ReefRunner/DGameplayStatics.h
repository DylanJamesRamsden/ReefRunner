// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "DGameplayStatics.generated.h"

class ADGameplayGameMode;
class ADGameplayGameState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API UDGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

public:

	static ADGameplayGameMode* GetDGameplayGameMode(const UObject* WorldContext);

	static ADGameplayGameState* GetDGameplayGameState(const UObject* WorldContext);
	
};
