// Fill out your copyright notice in the Description page of Project Settings.


#include "DCleanUpBox.h"

#include "DPlatform.h"
#include "DPlatformGenerator.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADCleanUpBox::ADCleanUpBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");

	RootComponent = BoxComp;

	BoxComp->SetBoxExtent(FVector(50.0f, 1000.0f, 1000.0f));
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxComp->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ADCleanUpBox::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		AttachToActor(PlayerPawn, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ADCleanUpBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (ADPlatform* OverlappingPlatform = Cast<ADPlatform>(OtherActor))
	{
		MyPlatformGenerator->SpawnPlatform();
	}

	OtherActor->Destroy();
}

// Called every frame
void ADCleanUpBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADCleanUpBox::SetPlatformGenerator(ADPlatformGenerator* PlatformGenerator)
{
	MyPlatformGenerator = PlatformGenerator;
}



