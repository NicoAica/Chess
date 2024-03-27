// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameField.h"
#include "PlayerInterface.h"
#include "Piece.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "HumanPlayer.generated.h"

UCLASS()
class CHESS_API AHumanPlayer : public APawn, public IPlayerInterface
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Keeps track turn
	bool IsMyTurn = false;

	// Flag to keep if is the first or second click on tile
	bool IsFirstClick = true;

	// Keep the selected piece (Uso UProp to avoid Garbage Collection problem)
	UPROPERTY()
	APiece *SelectedPiece = nullptr;

	void MoveActorTo(ATile* FutureTile);
	void MoveActorTo(APiece* EvilPiece);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Override OnTurn function
	void OnTurn() override;

	UFUNCTION()
	void OnClick();

	// Sets default values for this pawn's properties
	AHumanPlayer();

	// Human camera
	UCameraComponent *Camera;

private:
	int PlayerNumber;
};
