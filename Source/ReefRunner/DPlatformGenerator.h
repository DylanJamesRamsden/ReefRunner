// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPlatformGenerator.generated.h"

class ADPlatform;
class ADCleanUpBox;

	// General note to self:
	// X axis if forward in the spawners case
	// Y axis is right in the spawners case

UCLASS()
class REEFRUNNER_API ADPlatformGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPlatformGenerator();

protected:

	//How long it takes for a platform to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float PlatformSpawnTime;

	FTimerHandle PlatformSpawnTimerHandle;
	
	// The number of platforms that is spawned initially at game start
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int MaxPlatforms = 20;

	// Where the first segment of a platform spawns
	FVector SpawnOrigin;

	// The platform template to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ADPlatform> PlatformTemplate;

	UPROPERTY()
	TArray<ADPlatform*> Platforms;

	// How many platforms need to pass before spawning a new pick-up platform
	// can be considered
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|PickUps")
	int PlatformsBetweenPickups = 10;

	int PlatformsSinceLastPickUp;

	// The max number of pick-ups a platform can spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|PickUps")
	int MaxPickUpsPerPlatform = 2;

	// The chance a pick-up platform will be spawned once the number of platforms spawned
	// exceeds the PlatformsBetweenPickUps
	// (0 - PickUpPlatformSpawnVariance == PickUpPlatformSpawnVariance)
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|PickUps")
	int PickUpPlatformSpawnVariance;

	// The chance a segment in a pick-up platform has in order to spawn a pick-up
	// (0 - PickUpSpawnVariance == PickUpSpawnVariance)
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|PickUps")
	int PickUpSpawnVariance;

	// How many platforms need to pass before spawning a new obstacle platform
	// can be considered
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Obstacles")
	int PlatformsBetweenObstacles = 10;

	int PlatformsSinceLastObstacle;

	// The max number of obstacles a platform can spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Obstacles")
	int MaxObstaclesPerPlatform = 2;

	// The chance a obstacle platform will be spawned once the number of platforms spawned
	// exceeds the PlatformsBetweenObstacles
	// (0 - ObstaclePlatformSpawnVariance == ObstaclePlatformSpawnVariance)
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Obstacles")
	int ObstaclesPlatformSpawnVariance;

	// The chance a segment in a obstacle platform has in order to spawn a obstacle
	// (0 - ObstacleSpawnVariance == ObstacleSpawnVariance)
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Obstacles")
	int ObstacleSpawnVariance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADCleanUpBox> CleanUpBoxTemplate;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SpawnPlatform();

	// ¬ LEVEL TRANSITION
	
	UPROPERTY(EditDefaultsOnly, Category = "Level Transition")
	TArray<FLinearColor> LevelColors;
	
	bool bIsTransitioningLevel;

	// THis could easily be done with a FVector2D (X for from and Y for to) but just clearer this way
	int32 LevelToTransitionFrom;
	int32 LevelToTransitionTo;

	// How many platforms it takes to transition from one level to another
	UPROPERTY(EditDefaultsOnly, Category = "Level Transition")
	float NumberOfPlatformsForTransition = 15;

	float CurrentPlatformsTransitioned;

	FLinearColor CurrentPlatformColor;
	
	UFUNCTION()
	void StartLevelTransition(int32 NewLevel);
	
	// ¬ END LEVEL TRANSITION

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
