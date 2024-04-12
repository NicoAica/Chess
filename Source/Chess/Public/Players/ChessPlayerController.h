// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUD/MoveHUD.h"
#include "ChessPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessPlayerController : public APlayerController
{
	GENERATED_BODY()

	AChessPlayerController();
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* Context;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputAction;
	
	void ClickOnGrid();

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Interface")
	UMoveHUD* MoveHUD;
};
