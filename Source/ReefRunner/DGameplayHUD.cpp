// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayHUD.h"

#include "DGameplayGameState.h"
#include "Widgets/DPrePlayWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ADGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld()))
	{
		if (ADGameplayGameState* DGameState = Cast<ADGameplayGameState>(GameState))
		{
			DGameState->OnGameplayStateChanged.AddDynamic(this, &ADGameplayHUD::OnGameplayStateChanged);
		}
	}
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
				PrePlayWidgetRef->OnGameplayStateChanged(NewState);
				PrePlayWidgetRef->AddToViewport(1);
			}
			else UE_LOG(LogTemp, Error, TEXT("Failed to create StartScreenWidget!"));	
		}
		else UE_LOG(LogTemp, Error, TEXT("Please assign PrePlayScreenWidgetClass in DGameplayHUD!"));	
	}
}
