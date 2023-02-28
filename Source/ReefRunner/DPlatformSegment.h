// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "DPlatformSegment.generated.h"

UCLASS()
class REEFRUNNER_API ADPlatformSegment : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPlatformSegment();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// How large a platform segment is (in width)
	// Using generic UE cube for now, so they are 1m (100.0cm)
	UPROPERTY(EditDefaultsOnly)
	float SegmentWidth = 100.0f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
