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
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ~ MOVEMENT
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultMovementIMC;
	
	UPROPERTY(EditDefaultsOnly)
	UDDefaultMovementConfig* DefaultMovementConfig;

	bool bCanInterpHorizontalLocation;
	
	FVector HorizontalTargetLocation;

	UPROPERTY(EditDefaultsOnly)
	float HorizontalInterpSpeed = 50.0f;

	void HorizontalMovement(const FInputActionValue& Value);

	/** Notifies when DCharacter is moving horizontally
	 * @param Direction The horizontal direction in which DCharacter is moving */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnMovingHorizontally(FVector Direction);

	// Notifies when DCharacter has completed it's horizontal movement
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnMovingHorizontallyComplete();

	// ~ END MOVEMENT

	// ~ JUMPING

	virtual void Jump() override;

	bool bIsJumping;

	// Notifies when DCharacter has started jumping
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnJumpingStarted();

	// Notifies when DCharacter has completed it's jump (landed)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnJumpingComplete();

	// ~ END JUMPING

	// ~ ACHARACTER OVERRIDES
	virtual void Landed(const FHitResult& Hit) override;
	// ~ END ACHARACTER OVERRIDES

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ~ APAWN OVERRIDES
	virtual void PossessedBy(AController* NewController) override;
	// ~ END APAWN OVERRIDES
};
