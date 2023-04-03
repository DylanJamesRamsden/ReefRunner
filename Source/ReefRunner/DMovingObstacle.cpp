// Fill out your copyright notice in the Description page of Project Settings.


#include "DMovingObstacle.h"

#include "GameFramework/FloatingPawnMovement.h"

ADMovingObstacle::ADMovingObstacle()
{
	
}

void ADMovingObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(GetActorLocation() + (MovementDirection * MovementSpeed));
}
