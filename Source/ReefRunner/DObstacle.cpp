// Fill out your copyright notice in the Description page of Project Settings.


#include "DObstacle.h"

#include "Components/BoxComponent.h"

// Sets default values
ADObstacle::ADObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComp");

	StaticMeshComp->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(RootComponent);

	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

