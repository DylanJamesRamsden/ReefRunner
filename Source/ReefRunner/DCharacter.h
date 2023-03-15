// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UDDefaultMovementConfig;
struct FInputActionValue;

UCLASS()
class REEFRUNNER_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

protected:

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultMovementIMC;
	
	UPROPERTY(EditDefaultsOnly)
	UDDefaultMovementConfig* DefaultMovementConfig;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HorizontalMovement(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
};
