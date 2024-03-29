// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCleanUpBox.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlatformDestroyed);

UCLASS()
class REEFRUNNER_API ADCleanUpBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADCleanUpBox();

protected:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	FPlatformDestroyed OnPlatformDestroyed;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
