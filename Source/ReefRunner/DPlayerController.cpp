// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "DDefaultMovementConfig.h"
#include "DGameplayGameMode.h"
#include "DGameplayGameState.h"
#include "DGameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		// Binds to the gameplay state change in DGameplayGameState
		DGameState->OnGameplayStateChanged.AddDynamic(this, &ADPlayerController::OnGameplayStateChanged);
	}

	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void ADPlayerController::StartGame()
{
	if (const ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		if (DGameState->GetCurrentGameplayState() == WaitingToStart)
		{
			if (ADGameplayGameMode* DGameMode = UDGameplayStatics::GetDGameplayGameMode(this))
			{
				DGameMode->OnStartInitiated();

				// @TODO Just remove the binding in the future
				DisableInput(this);
			}
			else UE_LOG(LogTemp, Warning, TEXT("Could not find DGameplayGameMode when trying to start game in %s! %s!"), *GetName());	
		}
	}
	else UE_LOG(LogTemp, Warning, TEXT("Could not find DGameplayGameState when trying to start game in %s!"), *GetName());	
}

void ADPlayerController::OnGameplayStateChanged(EGameplayState NewState)
{
	if (NewState == Ended)
	{
		SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
	}
}

void ADPlayerController::SetupInputComponent()
{
	// So we actually do need Super as it creates the InputComponent
	Super::SetupInputComponent();
	
	if (InputComponent)
	{
		if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
			check(InteractionConfig);
			EnhancedInputSubsystem->AddMappingContext(InteractionIMC, 0);

			UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
			EnhancedInputComponent->BindAction(InteractionConfig->StartGameIA, ETriggerEvent::Triggered, this, &ADPlayerController::StartGame);
		}
		else UE_LOG(LogTemp, Error, TEXT("Could not find Local Player when setting up input in %s!"), *GetName());	
	}
	else UE_LOG(LogTemp, Error, TEXT("No Input Component in %s! Better do something about that!"), *GetName());	
}
