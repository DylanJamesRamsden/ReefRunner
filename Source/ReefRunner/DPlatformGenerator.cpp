// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatformGenerator.h"

#include "DPlatform.h"

// Sets default values
ADPlatformGenerator::ADPlatformGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADPlatformGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (PlatformTemplate)
	{
		SpawnOrigin.X = GetActorLocation().X;
		SpawnOrigin.Y = GetActorLocation().Y;

		GetWorldTimerManager().SetTimer(PlatformSpawnTimerHandle, this, &ADPlatformGenerator::SpawnPlatform, PlatformSpawnTime, true);	
	}
}

void ADPlatformGenerator::SpawnPlatform()
{
	ADPlatform* NewPlatform = GetWorld()->SpawnActor<ADPlatform>(PlatformTemplate, SpawnOrigin, FRotator::ZeroRotator);
	if (NewPlatform)
	{
		PlatformsSinceLastPickUp++;
		PlatformsSinceLastObstacle++;

		bool bCanSpawnPickUp = false;
		if (PlatformsSinceLastPickUp >= PlatformsBetweenPickups)
		{
			// Min and Max inclusive
			bCanSpawnPickUp = FMath::RandRange(0, PickUpPlatformSpawnVariance) == PickUpPlatformSpawnVariance;
		}

		bool bCanSpawnObstacle = false;
		if (PlatformsSinceLastObstacle >= PlatformsBetweenObstacles)
		{
			bCanSpawnObstacle = FMath::RandRange(0, ObstaclesPlatformSpawnVariance) == ObstaclesPlatformSpawnVariance;
		}
		
		NewPlatform->SpawnSegments(bSpawningFromRight,
			bCanSpawnPickUp,
			MaxPickUpsPerPlatform,
			PickUpSpawnVariance,
			bCanSpawnObstacle,
			MaxObstaclesPerPlatform,
			ObstacleSpawnVariance);

		if (bCanSpawnPickUp)
		{
			PlatformsSinceLastPickUp = 0;
		}

		if (bCanSpawnObstacle)
		{
			PlatformsSinceLastObstacle = 0;
		}

		SpawnOrigin.X = SpawnOrigin.X + 100.0f;

		if (!bSpawningFromRight)
		{
			bSpawningFromRight = true;
		}
		else
		{
			bSpawningFromRight = false;
		}

		Platforms.Add(NewPlatform);

		if (Platforms.Num() == MaxPlatforms)
		{
			if (GetWorldTimerManager().TimerExists(PlatformSpawnTimerHandle))
			{
				GetWorldTimerManager().ClearTimer(PlatformSpawnTimerHandle);
			}
		}	
	}
}

// Called every frame
void ADPlatformGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

