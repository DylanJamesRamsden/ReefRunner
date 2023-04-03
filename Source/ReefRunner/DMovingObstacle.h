// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DObstacle.h"
#include "DMovingObstacle.generated.h"

class UFloatingPawnMovement;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADMovingObstacle : public ADObstacle
{
	GENERATED_BODY()

public:

	ADMovingObstacle();	

protected:

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly)
	FVector MovementDirection;

	virtual void Tick(float DeltaSeconds) override;
};
