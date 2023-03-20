// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatform.h"

#include "DObstacle.h"
#include "DPickUp.h"

// Sets default values
ADPlatform::ADPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector Extent = FVector(StaticMeshComp->GetStaticMesh()->GetExtendedBounds().BoxExtent);
	const float Divisor = (Extent.Y * 2) / 7;
	
	FVector CurrentSpawnSlotLocation = RootComponent->GetComponentLocation() -
		FVector(0.0f, Divisor * FMath::Floor(Extent.Y/Divisor), -Extent.Z * 2);
	
	for (int i = 0; i < Extent.Y * 2 / Divisor; i++)
	{
		DrawDebugPoint(GetWorld(), CurrentSpawnSlotLocation, 10, FColor::Red, false, 2.0f);

		SpawnSlotLocations.Add(CurrentSpawnSlotLocation);
		
		CurrentSpawnSlotLocation += FVector(0.0f, 100.0f, 0.0f);
	}
}

// Called every frame
void ADPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPlatform::SpawnSegments(bool bShouldSpawnFromRight, bool bCanSpawnPickUp, int MaxPickUps, int PickUpSpawnVariance,
	bool bCanSpawnObstacles, int MaxObstacles, int ObstacleSpawnVariance)
{
	/*SpawnOrigin.X = GetActorLocation().X;

	if (bShouldSpawnFromRight)
	{
		SpawnOrigin.Y = GetActorLocation().Y + (((NumSegmentsToSpawn - 1)/2) * 100);
	}
	else
	{
		SpawnOrigin.Y = GetActorLocation().Y - (((NumSegmentsToSpawn - 1)/2) * 100);
	}

	bSpawningFromRight = bShouldSpawnFromRight;

	for (int i = 0; i < NumSegmentsToSpawn; i++)
	{
		ADPlatformSegment* NewSegment = GetWorld()->SpawnActor<ADPlatformSegment>(SegmentTemplate);
		NewSegment->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
		NewSegment->SetActorLocation(SpawnOrigin);

		bool bOccupied = false;
		if (bCanSpawnPickUp)
		{
			if (MaxPickUps != 0)
			{
				if (FMath::RandRange(0, PickUpSpawnVariance) == PickUpSpawnVariance)
				{
					NewSegment->SpawnPickUp();
					MaxPickUps--;
					bOccupied = true;
				}
			}
		}

		if (bCanSpawnObstacles && !bOccupied)
		{
			if (MaxObstacles != 0)
			{
				if (FMath::RandRange(0, ObstacleSpawnVariance) == ObstacleSpawnVariance)
				{
					NewSegment->SpawnObstacle();
					MaxObstacles--;
				}
			}
		}

		if (bSpawningFromRight)
		{
			SpawnOrigin.Y = SpawnOrigin.Y - NewSegment->SegmentWidth;
		}
		else
		{
			SpawnOrigin.Y = SpawnOrigin.Y + NewSegment->SegmentWidth;
		}

		Segments.Add(NewSegment);
	}*/
}

void ADPlatform::SpawnPickUp()
{
	if (PickUpTemplate)
	{
		if (ADPickUp* NewPickUp = GetWorld()->SpawnActor<ADPickUp>(PickUpTemplate))
		{
			MyPickUps.Add(NewPickUp);
			NewPickUp->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 150.0f));	
		}
	}
}

void ADPlatform::SpawnObstacle()
{
	if (ObstacleTemplate)
	{
		if (ADObstacle* NewObstacle = GetWorld()->SpawnActor<ADObstacle>(ObstacleTemplate))
		{
			MyObstacles.Add(NewObstacle);
			NewObstacle->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 50.0f));	
		}
	}
}

