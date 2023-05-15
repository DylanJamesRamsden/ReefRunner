// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayHUD.h"

#include "DGameplayGameState.h"
#include "DGameplayStatics.h"
#include "Widgets/DPrePlayWidget.h"
#include "Blueprint/UserWidget.h"

void ADGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
	{
		DGameState->OnGameplayStateChanged.AddDynamic(this, &ADGameplayHUD::OnGameplayStateChanged);
	}

#if WITH_EDITOR
	if (DebugWidgetClass)
	{
		if (UUserWidget* DebugWidgetRef = CreateWidget<UUserWidget>(PlayerOwner, DebugWidgetClass))
		{
			DebugWidgetRef->AddToViewport(2);
		}
	}
#endif
}

void ADGameplayHUD::OnGameplayStateChanged(EGameplayState NewState)
{
	if (NewState == Generating)
	{
		if (PrePlayWidgetClass)
		{
			PrePlayWidgetRef = CreateWidget<UDPrePlayWidget>(PlayerOwner, PrePlayWidgetClass);
			if (PrePlayWidgetRef)
			{
				if (ADGameplayGameState* DGameState = UDGameplayStatics::GetDGameplayGameState(this))
				{
					DGameState->OnGameplayStateChanged.AddDynamic(PrePlayWidgetRef, &UDPrePlayWidget::OnGameplayStateChanged);
				}
				
				PrePlayWidgetRef->AddToViewport(1);
			}
			else UE_LOG(LogTemp, Error, TEXT("Failed to create StartScreenWidget!"));	
		}
		else UE_LOG(LogTemp, Error, TEXT("Please assign PrePlayScreen widget class in DGameplayHUD!"));	
	}
	else if (NewState == Started)
	{
		if (PrePlayWidgetRef)
		{
			PrePlayWidgetRef->RemoveFromParent();
			PrePlayWidgetRef = nullptr;
		}

		if (GameplayHUDWidgetClass)
		{
			GameplayHUDWidgetRef = CreateWidget<UUserWidget>(PlayerOwner, GameplayHUDWidgetClass);
			if (GameplayHUDWidgetRef)
			{
				GameplayHUDWidgetRef->AddToViewport(1);
			}
			else UE_LOG(LogTemp, Error, TEXT("Failed to create GameplayHUD widget!"));	
		}
		else UE_LOG(LogTemp, Error, TEXT("Please assign GameplayHUD widget class in DGameplayHUD!"));	
	}
	else if (NewState == Ended)
	{
		FTimerHandle EndGameWidgetTimerHandle;
		GetWorldTimerManager().SetTimer(EndGameWidgetTimerHandle, this, &ADGameplayHUD::SpawnEndGameWidget, 2.0f);
	}
}

void ADGameplayHUD::SpawnEndGameWidget()
{
	if (GameplayHUDWidgetRef)
	{
		GameplayHUDWidgetRef->RemoveFromParent();
		GameplayHUDWidgetRef = nullptr;
	}

	if (EndGameWidgetClass)
	{
		EndGameWidgetRef = CreateWidget<UUserWidget>(PlayerOwner, EndGameWidgetClass);
		if (EndGameWidgetRef)
		{
			EndGameWidgetRef->AddToViewport(1);
		}
		else UE_LOG(LogTemp, Error, TEXT("Failed to create EndGame widget!"));	
	}
	else UE_LOG(LogTemp, Error, TEXT("Please assign EndGame widget class in DGameplayHUD!"));	
}
