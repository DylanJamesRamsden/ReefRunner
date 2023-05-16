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
enum EGameplayState;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* SubmarineBodyMesh;
	
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

	// A 2D Vector representing the limit of how far the Character can move horizontally. X is 300 added onto the starting
	// location's Y and Y is 300 subtracted from the starting location's Y (e.g. X = 300 and Y = -300)
	FVector2D HorizontalMovementClamp;

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

	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState NewState);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ~ APAWN OVERRIDES
	virtual void PossessedBy(AController* NewController) override;
	// ~ END APAWN OVERRIDES
};
