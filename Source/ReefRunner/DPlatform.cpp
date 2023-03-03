// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatform.h"

#include "DPlatformSegment.h"

// Sets default values
ADPlatform::ADPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPlatform::SpawnSegments(bool bShouldSpawnFromRight, bool bCanSpawnPickUp, int MaxPickUps, int PickUpSpawnVariance)
{
	SpawnOrigin.X = GetActorLocation().X;

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

		if (bCanSpawnPickUp)
		{
			if (MaxPickUps != 0)
			{
				if (FMath::RandRange(0, PickUpSpawnVariance) == PickUpSpawnVariance)
				{
					NewSegment->SpawnPickUp();
					MaxPickUps--;
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
	}
}

