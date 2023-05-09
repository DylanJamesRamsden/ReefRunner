// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DDefaultMovementConfig.h"
#include "DGameplayGameState.h"
#include "DGameplayStatics.h"
#include "DObstacle.h"
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
	PrimaryActorTick.bStartWithTickEnabled = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	SubmarineBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("SubmarineBodyMesh");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
	SubmarineBodyMesh->SetupAttachment(RootComponent);

	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 7.5f;
	SpringArmComp->TargetArmLength = 600.0f;
	SpringArmComp->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	SpringArmComp->bDoCollisionTest = false;

	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->bNotifyApex = true;
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		// Binds to the gameplay state change in DGameplayGameState
		DGameState->OnGameplayStateChanged.AddDynamic(this, &ADCharacter::OnGameplayStateChanged);
	}

	// Set's the Horizontal Movement Clamp (how far the Character can move horizontally) based on the Character's
	// starting location
	HorizontalMovementClamp.X = GetActorLocation().Y + 300.f;
	HorizontalMovementClamp.Y = GetActorLocation().Y - 300.f;
}

void ADCharacter::HorizontalMovement(const FInputActionValue& Value)
{
	if (HorizontalTargetLocation.Y + (Value.Get<float>() * 100.f) <= HorizontalMovementClamp.X &&
		HorizontalTargetLocation.Y + (Value.Get<float>() * 100.f) >= HorizontalMovementClamp.Y)
	{
		if (!bCanInterpHorizontalLocation)
		{
			bCanInterpHorizontalLocation = true;
			HorizontalTargetLocation = GetActorLocation() + ((GetActorRightVector() + Value.Get<float>() * 100.0f) - GetActorRightVector());
		}
		else
		{
			HorizontalTargetLocation = FVector(HorizontalTargetLocation.X, HorizontalTargetLocation.Y + Value.Get<float>() * 100.0f, HorizontalTargetLocation.Z);
		}

		OnMovingHorizontally(GetActorRightVector() + Value.Get<float>());
	}
}

void ADCharacter::Jump()
{
	Super::Jump();

	OnJumpingStarted();

	bIsJumping = true;
}

void ADCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bIsJumping)
	{
		OnJumpingComplete();

		bIsJumping = false;
	}
}

void ADCharacter::OnGameplayStateChanged(EGameplayState NewState)
{
	switch (NewState)
	{
		case Started:
			SetActorTickEnabled(true);

			if (Controller)
			{
				if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
				{
					EnableInput(PlayerController);
				}
			}
			break;
	}
}

void ADCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Other->IsA(ADObstacle::StaticClass()))
	{
		SubmarineBodyMesh->SetSimulatePhysics(true);
	}
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector() * .4f);

	if (bCanInterpHorizontalLocation)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), FVector(GetActorLocation().X, HorizontalTargetLocation.Y, GetActorLocation().Z), DeltaTime, HorizontalInterpSpeed));
		
		// (Cosmetic!!) Added this extra check to allow time for the Character's rotation to be leveled out when reaching it's
		// horizontal destination
		if (UKismetMathLibrary::NearlyEqual_FloatFloat(GetActorLocation().Y, HorizontalTargetLocation.Y, 2.0F))
		{
			OnMovingHorizontallyComplete();
		}

		if (UKismetMathLibrary::NearlyEqual_FloatFloat(GetActorLocation().Y, HorizontalTargetLocation.Y, 0.1F))
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

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		// Removed this as I also have input on DPlayerController
		// EnhancedInputSubsystem->ClearAllMappings();
		check(DefaultMovementIMC);
		EnhancedInputSubsystem->AddMappingContext(DefaultMovementIMC, 0);

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		EnhancedInputComponent->BindAction(DefaultMovementConfig->HorizontalMovementIA, ETriggerEvent::Triggered, this, &ADCharacter::HorizontalMovement);
		EnhancedInputComponent->BindAction(DefaultMovementConfig->JumpIA, ETriggerEvent::Triggered, this, &ADCharacter::Jump);

		DisableInput(PlayerController);
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

