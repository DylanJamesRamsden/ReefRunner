// Fill out your copyright notice in the Description page of Project Settings.


#include "DPickUp.h"

#include "DPlayerState.h"
#include "Components/SphereComponent.h"

// Sets default values
ADPickUp::ADPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Manually setting the RootComp as a SceneComp, was throwing a weird warning so just clearing up the log spam
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");

	StaticMeshComp->SetupAttachment(RootComponent);
	SphereComp->SetupAttachment(StaticMeshComp);

	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (APawn* OtherPawn = Cast<APawn>(OtherActor))
	{
		Destroy();
	}
}

void ADOxygenBubble::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (const APawn* OverlappingPawn = Cast<APawn>(OtherActor))
	{
		if (ADPlayerState* DPlayerState = OverlappingPawn->GetPlayerState<ADPlayerState>())
		{
			DPlayerState->AddOxygen(OxygenAmount);
		}
	}
	
	Super::NotifyActorBeginOverlap(OtherActor);
}

