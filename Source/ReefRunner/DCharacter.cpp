// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DDefaultMovementConfig.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->bEnableCameraLag;
	SpringArmComp->TargetArmLength = 600.0f;
	SpringArmComp->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	SpringArmComp->bDoCollisionTest = false;

	GetCharacterMovement()->JumpZVelocity = 600.0f;
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacter::HorizontalMovement(const FInputActionValue& Value)
{
	if (!bCanInterpHorizontalLocation)
	{
		bCanInterpHorizontalLocation = true;
		HorizontalTargetLocation = GetActorLocation() + (GetActorRightVector() + Value.Get<float>() * 100.0f);
	}
	else
	{
		HorizontalTargetLocation = FVector(HorizontalTargetLocation.X, HorizontalTargetLocation.Y + Value.Get<float>() * 100.0f, HorizontalTargetLocation.Z);
	}
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector() * .2f);

	if (bCanInterpHorizontalLocation)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), FVector(GetActorLocation().X, HorizontalTargetLocation.Y, GetActorLocation().Z), DeltaTime, 15.0f));

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(GetActorLocation().Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(HorizontalTargetLocation.Y));

		if (UKismetMathLibrary::NearlyEqual_FloatFloat(GetActorLocation().Y, HorizontalTargetLocation.Y, 0.0001F))
		{
			SetActorLocation(FVector(GetActorLocation().X, HorizontalTargetLocation.Y, GetActorLocation().Z));
			bCanInterpHorizontalLocation = false;
		}
	}
}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		EnhancedInputSubsystem->ClearAllMappings();
		check(DefaultMovementIMC);
		EnhancedInputSubsystem->AddMappingContext(DefaultMovementIMC, 0);

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		EnhancedInputComponent->BindAction(DefaultMovementConfig->HorizontalMovementIA, ETriggerEvent::Triggered, this, &ADCharacter::HorizontalMovement);
		EnhancedInputComponent->BindAction(DefaultMovementConfig->JumpIA, ETriggerEvent::Triggered, this, &ADCharacter::Jump);
	}
}

void ADCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PC = Cast<APlayerController>(NewController))
	{
		PC->SetViewTarget(this);
	}
}

