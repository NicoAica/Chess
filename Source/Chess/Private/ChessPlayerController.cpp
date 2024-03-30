// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"

#include "Players/HumanPlayer.h"

AChessPlayerController::AChessPlayerController()
{
	
	bShowMouseCursor = true;
	SetShowMouseCursor(true);

	bEnableClickEvents = true;
}

void AChessPlayerController::ClickOnGrid()
{
	 if (const auto HumanPlayer = Cast<AHumanPlayer>(GetPawn()); IsValid(HumanPlayer))
	 {
		 HumanPlayer->OnClick();
	 }
}

void AChessPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(Context, 0);
	}
	
}

void AChessPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &AChessPlayerController::ClickOnGrid);
	}
}
