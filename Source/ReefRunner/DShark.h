// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMovingObstacle.h"
#include "DShark.generated.h"

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADShark : public ADMovingObstacle
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	float ObstacleDetectionDistance;

	UPROPERTY(EditDefaultsOnly)
	float HorizontalInterpSpeed = 200.0f;

	FVector TargetLocation;

	bool bCanInterpHorizontalLocation;

	virtual void Tick(float DeltaSeconds) override;

	bool IsOverlappingObstacleAtLocation(FVector Location, TArray<AActor*>& OutActors) const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnMovingHorizontally(float Direction);

	// Notifies when DCharacter has completed it's horizontal movement
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnMovingHorizontallyComplete();
};
