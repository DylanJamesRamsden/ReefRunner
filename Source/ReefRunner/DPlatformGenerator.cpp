// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatformGenerator.h"

#include "DCleanUpBox.h"
#include "DGameplayGameMode.h"
#include "DGameplayGameState.h"
#include "DGameplayStatics.h"
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

	if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		DGameState->OnGameplayStateChanged.AddDynamic(this, &ADPlatformGenerator::OnGameplayStateChanged);
			
		DGameState->OnLevelChanged.AddDynamic(this, &ADPlatformGenerator::StartLevelTransition);

		check(LevelColors.Num() == DGameState->GetMaxLevels())

		CurrentPlatformColor = LevelColors[DGameState->GetCurrentLevel() - 1];
	}
}

void ADPlatformGenerator::SpawnPlatform()
{
	if (!bIsSpawningTrench)
	{
		if (PlatformsSinceLastTrench >= PlatformsBetweenTrenches)
		{
			bIsSpawningTrench = FMath::RandRange(0, TrenchPlatformSpawnVariance) == TrenchPlatformSpawnVariance;
		}
	}
	
	ADPlatform* NewPlatform = nullptr;
	if (bIsSpawningTrench)
	{
		NewPlatform = GetWorld()->SpawnActor<ADPlatform>(TrenchTemplate, GetActorLocation(), FRotator::ZeroRotator);	
	}
	else NewPlatform = GetWorld()->SpawnActor<ADPlatform>(PlatformTemplate, GetActorLocation(), FRotator::ZeroRotator);	
	
	if (NewPlatform)
	{
		if (!bIsSpawningTrench)
		{
			PlatformsSinceLastPickUp++;
			PlatformsSinceLastObstacle++;
			PlatformsSinceLastTrench++;

			if (bIsTransitioningLevel)
			{
				CurrentPlatformsTransitioned++;
				CurrentPlatformColor = FLinearColor::LerpUsingHSV(LevelColors[LevelToTransitionFrom - 1], LevelColors[LevelToTransitionTo - 1], (1 / NumberOfPlatformsForTransition) * CurrentPlatformsTransitioned);
			
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, CurrentPlatformColor.ToFColor(true), TEXT("Transitioning platforms!"));

				if (CurrentPlatformsTransitioned == NumberOfPlatformsForTransition)
				{
					bIsTransitioningLevel = false;
				}
			}

			NewPlatform->SetColor(CurrentPlatformColor);

			bool bCanSpawnPickUp = false;
			if (PlatformsSinceLastPickUp >= PlatformsBetweenPickups)
			{
				// Min and Max inclusive
				bCanSpawnPickUp = FMath::RandRange(0, PickUpPlatformSpawnVariance) == PickUpPlatformSpawnVariance;
			}

			bool bCanSpawnObstacle = false;
			if (PlatformsSinceLastObstacle >= PlatformsBetweenObstacles)
			{
				bCanSpawnObstacle = FMath::RandRange(0, ObstaclesPlatformSpawnVariance) == ObstaclesPlatformSpawnVariance;
			}
		
			NewPlatform->InitializeSpawnSlots();
			NewPlatform->SpawnItems(bCanSpawnPickUp,
				MaxPickUpsPerPlatform,
				PickUpSpawnVariance,
				bCanSpawnObstacle,
				MaxObstaclesPerPlatform,
				ObstacleSpawnVariance);

			if (bCanSpawnPickUp)
			{
				PlatformsSinceLastPickUp = 0;
			}

			if (bCanSpawnObstacle)
			{
				PlatformsSinceLastObstacle = 0;
			}
		}
		else
		{
			TrenchesSpawned++;

			if (TrenchesSpawned >= MaxNumberOfTrenchesToSpawn)
			{
				bIsSpawningTrench = false;
				PlatformsSinceLastTrench = 0;
				TrenchesSpawned = 0;
			}
		}
		
		SetActorLocation(FVector(GetActorLocation().X + 100.0f, GetActorLocation().Y, GetActorLocation().Z));
		DrawDebugSphere(GetWorld(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100.0f),
			50, 26, FColor::Yellow, false, 3.0f, 0, 2);

		Platforms.Add(NewPlatform);

		if (Platforms.Num() == MaxPlatforms)
		{
			if (GetWorldTimerManager().TimerExists(PlatformSpawnTimerHandle))
			{
				GetWorldTimerManager().ClearTimer(PlatformSpawnTimerHandle);
			}

			if (bSpawningInitialPlatforms)
			{
				bSpawningInitialPlatforms = false;

				if (const ADGameplayGameMode* DGameMode = UDGameplayStatics::GetDGameplayGameMode(this))
				{
					DGameMode->OnGenerationComplete();
				}
			}
		}	
	}
}

// Called every frame
void ADPlatformGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADPlatformGenerator::StartLevelTransition(int32 NewLevel)
{
	CurrentPlatformsTransitioned = 0;
	
	if (const ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		if (DGameState->GetCurrentLevel() == 1)
		{
			LevelToTransitionFrom = DGameState->GetMaxLevels();
		}
		else LevelToTransitionFrom = DGameState->GetCurrentLevel() - 1;

		LevelToTransitionTo = DGameState->GetCurrentLevel();
	}
	else UE_LOG(LogTemp, Error, TEXT("Not using DGameState as default GameState when trying to transition paltform colors to new level in DPlatformGenerator!"));

	// If the 2 levels are equal, there is no point in trying to blend between the same level, just return
	if (LevelToTransitionFrom == LevelToTransitionTo)
		return;

	bIsTransitioningLevel = true;
}

void ADPlatformGenerator::OnGameplayStateChanged(EGameplayState NewState)
{
	if (NewState == Generating)
	{
		if (PlatformTemplate)
		{
			SpawnOrigin.X = GetActorLocation().X;
			SpawnOrigin.Y = GetActorLocation().Y;

			GetWorldTimerManager().SetTimer(PlatformSpawnTimerHandle, this, &ADPlatformGenerator::SpawnPlatform, PlatformSpawnTime, true);

			bSpawningInitialPlatforms = true;
		}

		if (CleanUpBoxTemplate)
		{
			ADCleanUpBox* NewCleanUpBox = GetWorld()->SpawnActor<ADCleanUpBox>(CleanUpBoxTemplate, GetActorLocation() + (GetActorForwardVector() * -500.0f), FRotator::ZeroRotator);
			NewCleanUpBox->OnPlatformDestroyed.AddDynamic(this, &ADPlatformGenerator::SpawnPlatform);
		}
	}
	else if (NewState == Started)
	{
		bSpawningInitialPlatforms = false;
	}
}

