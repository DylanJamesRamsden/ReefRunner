// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatformSegment.h"

#include "DObstacle.h"
#include "DPickUp.h"

// Sets default values
ADPlatformSegment::ADPlatformSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPlatformSegment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPlatformSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPlatformSegment::SpawnPickUp()
{
	if (PickUpTemplate)
	{
		if (ADPickUp* NewPickUp = GetWorld()->SpawnActor<ADPickUp>(PickUpTemplate))
		{
			MyPickUp = NewPickUp;
			NewPickUp->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 150.0f));	
		}
	}
}

void ADPlatformSegment::SpawnObstacle()
{
	if (ObstacleTemplate)
	{
		if (ADObstacle* NewObstacle = GetWorld()->SpawnActor<ADObstacle>(ObstacleTemplate))
		{
			MyObstacle = NewObstacle;
			NewObstacle->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 50.0f));	
		}
	}
}

