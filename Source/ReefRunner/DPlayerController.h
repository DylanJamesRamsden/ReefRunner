// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class UInputMappingContext;
class UDInteractionConfig;
enum EGameplayState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InteractionIMC;
	
	UPROPERTY(EditDefaultsOnly)
	UDInteractionConfig* InteractionConfig;

	virtual void BeginPlay() override;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState NewState);

public:
	
	virtual void SetupInputComponent() override;
};
