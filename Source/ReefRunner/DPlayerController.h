// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class UInputMappingContext;
class UDInteractionConfig;

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

	UFUNCTION()
	void StartGame();

public:
	
	virtual void SetupInputComponent() override;
};
