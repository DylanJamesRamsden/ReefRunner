// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlatform.h"

#include "DObstacle.h"
#include "DPickUp.h"
#include "Components/BoxComponent.h"

// Sets default values
ADPlatform::ADPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Manually setting the RootComp as a SceneComp, was throwing a weird warning so just clearing up the log spam
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	
	StaticMeshComp->SetupAttachment(RootComponent);
	BoxComp->SetupAttachment(RootComponent);

	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADPlatform::InitializeSpawnSlots()
{
	const FVector Extent = FVector(StaticMeshComp->GetStaticMesh()->GetExtendedBounds().BoxExtent);
	const float Divisor = (Extent.Y * 2) / 7;
	
	FVector CurrentSpawnSlotLocation = RootComponent->GetComponentLocation() -
		FVector(0.0f, Divisor * FMath::Floor(Extent.Y/Divisor), -Extent.Z * 2);
	
	for (int i = 0; i < Extent.Y * 2 / Divisor; i++)
	{
		// @TODO Add debug bool to toggle this
		//DrawDebugPoint(GetWorld(), CurrentSpawnSlotLocation, 10, FColor::Red, false, 2.0f);

		SpawnSlotLocations.Add(CurrentSpawnSlotLocation);
		
		CurrentSpawnSlotLocation += FVector(0.0f, 100.0f, 0.0f);
	}
}

// Called every frame
void ADPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPlatform::SpawnItems(bool bCanSpawnPickUp, int MaxPickUps, int PickUpSpawnVariance,
	bool bCanSpawnObstacles, int MaxObstacles, int ObstacleSpawnVariance)
{
	for (int i = 0; i < SpawnSlotLocations.Num(); i++)
	{
		bool bOccupied = false;
		if (bCanSpawnPickUp)
		{
			if (MaxPickUps != 0)
			{
				if (FMath::RandRange(0, PickUpSpawnVariance) == PickUpSpawnVariance)
				{
					SpawnPickUp(SpawnSlotLocations[i]);
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
					SpawnObstacle(SpawnSlotLocations[i]);
					MaxObstacles--;
				}
			}
		}
	}
}

void ADPlatform::SetColor(FLinearColor NewColor)
{
	if (UMaterialInterface* Material = StaticMeshComp->GetMaterial(0))
	{
		if (UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this))
		{
			DynamicMaterial->SetVectorParameterValue("Base Color", NewColor);
			StaticMeshComp->SetMaterial(0, DynamicMaterial);
		}
	}
}

void ADPlatform::SpawnPickUp(FVector Location)
{
	if (PickUpTemplate)
	{
		if (ADPickUp* NewPickUp = GetWorld()->SpawnActor<ADPickUp>(PickUpTemplate, Location + FVector(0.0f, 0.0f, 100.0f), FRotator::ZeroRotator))
		{
			MyPickUps.Add(NewPickUp);
		}
	}
}

void ADPlatform::SpawnObstacle(FVector Location)
{
	if (ObstacleTemplates.Num() > 0)
	{
		FActorSpawnParameters SpawnParams;
		if (ADObstacle* NewObstacle = GetWorld()->SpawnActor<ADObstacle>(ObstacleTemplates[FMath::RandRange(0, ObstacleTemplates.Num() - 1)], Location, FRotator::ZeroRotator))
		{
			MyObstacles.Add(NewObstacle);
		}
	}
	else UE_LOG(LogTemp, Warning, TEXT("No ObstacleTemplates set in %s, so cannot spawn any!"), *GetName());
}

