// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DPrePlayWidget.generated.h"

enum EGameplayState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API UDPrePlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnGameplayStateChanged(EGameplayState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown(float Duration);
	
};
