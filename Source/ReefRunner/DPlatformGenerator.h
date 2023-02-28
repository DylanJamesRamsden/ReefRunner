// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPlatformGenerator.generated.h"

class ADPlatform;

UCLASS()
class REEFRUNNER_API ADPlatformGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPlatformGenerator();

protected:

	//How long it takes for a platform to spawn
	UPROPERTY(EditDefaultsOnly)
	float PlatformSpawnTime;

	FTimerHandle PlatformSpawnTimerHandle;
	
	// The number of platforms that is spawned initially at game start
	UPROPERTY(EditDefaultsOnly)
	int MaxPlatforms = 20;

	// Where the first segment of a platform spawns
	FVector SpawnOrigin;

	bool SpawningFromRight = true;

	// The platform template to spawn
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADPlatform> PlatformTemplate;

	UPROPERTY()
	TArray<ADPlatform*> Platforms;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnPlatform();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
