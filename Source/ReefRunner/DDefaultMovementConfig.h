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

public:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* HorizontalMovementIA;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpIA;
};
