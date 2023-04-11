// Fill out your copyright notice in the Description page of Project Settings.


#include "DShark.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ADShark::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector ActorLocation = GetActorLocation();

	// If an obstacle is detected infront of the Shark, it looks for an open slot on either side of the obstacle. If
	// it finds one, it interps into the open slot (dodging the obstacle)
	if (!bCanInterpHorizontalLocation)
	{
		TArray<AActor*> OutForwardCheckActors;
		if (IsOverlappingObstacleAtLocation(ActorLocation + (MovementDirection * ObstacleDetectionDistance), OutForwardCheckActors))
		{
			TArray<AActor*> OutRightCheckActors;
			TArray<AActor*> OutLeftCheckActors;
		
			const bool bOverlappedObstacleOnRight = IsOverlappingObstacleAtLocation(OutForwardCheckActors[0]->GetActorLocation() + (GetActorRightVector() * 100), OutRightCheckActors);
			const bool bOverlappedObstacleOnLeft = IsOverlappingObstacleAtLocation(OutForwardCheckActors[0]->GetActorLocation() + (-GetActorRightVector() * 100), OutLeftCheckActors);

			bCanInterpHorizontalLocation = true;
			if (!bOverlappedObstacleOnRight)
			{
				TargetLocation = ActorLocation + (GetActorRightVector() * 100.0f);
			}
			else if (!bOverlappedObstacleOnLeft)
			{
				TargetLocation = ActorLocation + (-GetActorRightVector() * 100.0f);
			}
			else UE_LOG(LogTemp, Warning, TEXT("DShark only has logic to dodge 2 obstacles next to eachother! Look into this!"));
		}	
	}

	if (bCanInterpHorizontalLocation)
	{
		//SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaSeconds, 2.5f));
		const float NewY = FMath::FInterpConstantTo(ActorLocation.Y, TargetLocation.Y, DeltaSeconds, HorizontalInterpSpeed);
		SetActorLocation(FVector(ActorLocation.X, NewY, ActorLocation.Z));

		if (UKismetMathLibrary::NearlyEqual_FloatFloat(GetActorLocation().Y, TargetLocation.Y, 0.2F))
		{
			SetActorLocation(FVector(ActorLocation.X, TargetLocation.Y, ActorLocation.Z));
			bCanInterpHorizontalLocation = false;
		}
	}
}

bool ADShark::IsOverlappingObstacleAtLocation(FVector Location, TArray<AActor*>& OutActors) const
{
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	const TArray<AActor*> ActorsToIgnore;
	bool bOverlappedWithObstacle = UKismetSystemLibrary::BoxOverlapActors(GetWorld(), Location, FVector(10.0f, 10.0f, 10.0f), ObjectTypes,
		ADObstacle::StaticClass(), ActorsToIgnore, OutActors);

	if (!bOverlappedWithObstacle)
	{
		DrawDebugSphere(GetWorld(), Location, 20, 26, FColor::Green, false, 0.0f);
	}
	else DrawDebugSphere(GetWorld(), Location, 20, 26, FColor::Red, false, 0.0f);

	return bOverlappedWithObstacle;
}
