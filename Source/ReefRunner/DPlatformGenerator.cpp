// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatformGenerator.h"

#include "DCleanUpBox.h"
#include "DPlatform.h"
#include "Kismet/GameplayStatics.h"

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

	if (CleanUpBoxTemplate)
	{
		ADCleanUpBox* NewCleanUpBox = GetWorld()->SpawnActor<ADCleanUpBox>(CleanUpBoxTemplate, GetActorLocation() + (GetActorForwardVector() * -500.0f), FRotator::ZeroRotator);
		NewCleanUpBox->SetPlatformGenerator(this);
	}
}

void ADPlatformGenerator::SpawnPlatform()
{
	ADPlatform* NewPlatform = GetWorld()->SpawnActor<ADPlatform>(PlatformTemplate, GetActorLocation(), FRotator::ZeroRotator);
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
		
		NewPlatform->InitializeSpawnSlots();
		NewPlatform->SpawnItems(bCanSpawnPickUp,
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
		
		SetActorLocation(FVector(GetActorLocation().X + 100.0f, GetActorLocation().Y, GetActorLocation().Z));
		DrawDebugSphere(GetWorld(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100.0f),
			50, 26, FColor::Yellow, false, 3.0f, 0, 2);

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

