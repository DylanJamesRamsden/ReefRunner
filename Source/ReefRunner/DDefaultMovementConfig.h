// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DDefaultMovementConfig.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class REEFRUNNER_API UDDefaultMovementConfig : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HorizontalMovementIA;
};
