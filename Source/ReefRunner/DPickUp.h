// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPickUp.generated.h"

class USphereComponent;

UCLASS()
class REEFRUNNER_API ADPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPickUp();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};

UCLASS()
class REEFRUNNER_API ADOxygenBubble : public ADPickUp
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	float OxygenAmount;

public:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
