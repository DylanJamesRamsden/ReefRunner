// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPlatformGenerator.generated.h"

UCLASS()
class REEFRUNNER_API ADPlatformGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPlatformGenerator();

protected:

	// The number of platforms that is spawned initially at game start
	UPROPERTY(EditDefaultsOnly)
	int NumOfStartingPlatforms = 20;

	// How many individual static meshes make up a platform
	// @TODO It would be fun to randomize this
	UPROPERTY(EditDefaultsOnly)
	int NumOfSegmentsInPlatform = 7;

	// How large a platform segment is (in width)
	// Using generic UE cube for now, so they are 1m (100.0cm)
	UPROPERTY(EditDefaultsOnly)
	float SegmentWidth = 100.0f;

	// Where the first segment of a platform spawns
	FVector SpawnOrigin;

	bool SpawningFromRight = true;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* PlatformMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnPlatform(FVector PlatformOrigin);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
