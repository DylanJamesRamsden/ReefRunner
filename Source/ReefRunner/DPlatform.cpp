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

void ADPlatform::SpawnSegment()
{
	//DrawDebugBox(GetWorld(), FVector(SpawnOrigin), FVector(50,50,50), FColor::Green, true, -1, 0, 10);
			
	ADPlatformSegment* NewSegment = GetWorld()->SpawnActor<ADPlatformSegment>(SegmentTemplate);
	NewSegment->SetMobility(EComponentMobility::Movable);
	NewSegment->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	NewSegment->SetActorLocation(SpawnOrigin);

	if (bSpawningFromRight)
	{
		SpawnOrigin.Y = SpawnOrigin.Y - NewSegment->SegmentWidth;
	}
	else
	{
		SpawnOrigin.Y = SpawnOrigin.Y + NewSegment->SegmentWidth;
	}

	Segments.Add(NewSegment);

	if (Segments.Num() == NumSegmentsToSpawn)
	{
		if (GetWorldTimerManager().TimerExists(SegmentSpawnTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(SegmentSpawnTimerHandle);
		}	
	}
}

// Called every frame
void ADPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPlatform::StartSegmentSpawning(FVector Origin, bool bShouldSpawnFromRight)
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
	
	SpawnSegment();

	GetWorldTimerManager().SetTimer(SegmentSpawnTimerHandle, this, &ADPlatform::SpawnSegment, SegmentSpawnTime, true);
}

