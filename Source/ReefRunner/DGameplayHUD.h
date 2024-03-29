// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DGameplayHUD.generated.h"

class UDPrePlayWidget;
enum EGameplayState;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API ADGameplayHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDPrePlayWidget> PrePlayWidgetClass;

	UPROPERTY()
	UDPrePlayWidget* PrePlayWidgetRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GameplayHUDWidgetClass;

	UPROPERTY()
	UUserWidget* GameplayHUDWidgetRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	UPROPERTY()
	UUserWidget* EndGameWidgetRef;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DebugWidgetClass;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState NewState);

	UFUNCTION()
	void SpawnEndGameWidget();
};
