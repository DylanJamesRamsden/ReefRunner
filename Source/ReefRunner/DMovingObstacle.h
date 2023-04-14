// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DObstacle.h"
#include "DMovingObstacle.generated.h"

class UFloatingPawnMovement;
enum EGameplayState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADMovingObstacle : public ADObstacle
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly)
	FVector MovementDirection;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState NewState);
};
