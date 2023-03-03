// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPlatform.generated.h"

class ADPlatformSegment;

UCLASS()
class REEFRUNNER_API ADPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPlatform();

protected:

	// The segment template to spawn
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADPlatformSegment> SegmentTemplate;

	FVector SpawnOrigin;

	bool bSpawningFromRight;

	// How many individual static meshes make up a platform
	// @TODO It would be fun to randomize this
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int NumSegmentsToSpawn;

	UPROPERTY()
	TArray<ADPlatformSegment*> Segments;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnSegments(bool bShouldSpawnFromRight, bool bCanSpawnPickUp, int MaxPickUps);
};
