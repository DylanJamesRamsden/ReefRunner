// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

enum EGameplayState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	ADPlayerState();

	float LevelChangeScore = 100.0f;
	
	FVector StartingLocation;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState NewState);

	float Oxygen;

	UPROPERTY(EditDefaultsOnly)
	float OxygenStartingAmount;

	UPROPERTY(EditDefaultsOnly)
	float OxygenDecreaseTime;

	UPROPERTY(EditDefaultsOnly)
	float OxygenDecreaseAmount;

	FTimerHandle OxygenDecreaseTimerHandle;

	UFUNCTION()
	void DecreaseOxygen();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetLevelChangeScore();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetOxygen();
};
