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
	//DrawDebugBox(GetWorld(), GetActorLocation(), FVector(25,25,25), FColor::Yellow, true, -1, 0, 10);
	//DrawDebugBox(GetWorld(), SpawnOrigin, FVector(25,25,25), FColor::Red, true, -1, 0, 10);

	ADPlatform* NewPlatform = GetWorld()->SpawnActor<ADPlatform>(PlatformTemplate);
	if (NewPlatform)
	{
		PlatformsSinceLastPickUp++;

		bool bCanSpawnPickUp = false;
		if (PlatformsSinceLastPickUp >= PlatformsBetweenPickups)
		{
			// Min and Max inclusive
			bCanSpawnPickUp = FMath::RandRange(0, PickUpPlatformSpawnVariance) == PickUpPlatformSpawnVariance;
		}
		
		NewPlatform->SetActorLocation(SpawnOrigin);
		NewPlatform->SpawnSegments(bSpawningFromRight,
			bCanSpawnPickUp,
			MaxPickUpsPerPlatform,
			PickUpSpawnVariance);

		if (bCanSpawnPickUp)
		{
			PlatformsSinceLastPickUp = 0;
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

