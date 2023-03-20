// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPlatform.generated.h"

class ADObstacle;
class ADPickUp;

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
	UStaticMeshComponent* StaticMeshComp;

	FVector SpawnOrigin;

	bool bSpawningFromRight;

	// How many individual static meshes make up a platform
	// @TODO It would be fun to randomize this
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int NumSegmentsToSpawn;

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> SpawnSlotLocations;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADPickUp> PickUpTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADObstacle> ObstacleTemplate;

	UPROPERTY()
	TArray<ADPickUp*> MyPickUps;

	UPROPERTY()
	TArray<ADObstacle*> MyObstacles;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnPickUp();

	void SpawnObstacle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnSegments(bool bShouldSpawnFromRight, bool bCanSpawnPickUp, int MaxPickUps, int PickUpSpawnVariance,
		bool bCanSpawnObstacles, int MaxObstacles, int ObstacleSpawnVariance);
};
