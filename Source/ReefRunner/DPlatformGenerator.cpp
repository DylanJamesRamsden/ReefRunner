// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatformGenerator.h"

#include "Engine/StaticMeshActor.h"

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

	const FVector ActorLocation = GetActorLocation();

	for (int PlatformID = 0; PlatformID < NumOfStartingPlatforms; PlatformID++) // X
	{
		SpawnOrigin.X = ActorLocation.X + (PlatformID * SegmentWidth);
		// Resets the Y axis origin point
		SpawnOrigin.Y = ActorLocation.Y + (((NumOfSegmentsInPlatform - 1)/2) * SegmentWidth);

		DrawDebugBox(GetWorld(), GetActorLocation(), FVector(25,25,25), FColor::Yellow, true, -1, 0, 10);
		DrawDebugBox(GetWorld(), SpawnOrigin, FVector(25,25,25), FColor::Red, true, -1, 0, 10);

		SpawnPlatform(SpawnOrigin);
	}
}

void ADPlatformGenerator::SpawnPlatform(FVector PlatformOrigin)
{
	for (int SegmentID = 0; SegmentID < NumOfSegmentsInPlatform; SegmentID++) // Y
	{
		DrawDebugBox(GetWorld(), FVector(PlatformOrigin), FVector(50,50,50), FColor::Green, true, -1, 0, 10);
			
		AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
		MyNewActor->SetMobility(EComponentMobility::Movable);
		MyNewActor->SetActorLocation(PlatformOrigin);
		if (UStaticMeshComponent* MeshComp = MyNewActor->GetStaticMeshComponent())
		{
			MeshComp->SetStaticMesh(PlatformMesh);
		}

		PlatformOrigin.Y = PlatformOrigin.Y - SegmentWidth;
	}
}

// Called every frame
void ADPlatformGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

