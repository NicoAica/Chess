// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pieces/Piece.h"
#include "Engine/GameInstance.h"
#include "HUD/MoveHUD.h"
#include "Supports/Move.h"
#include "ChessGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UPROPERTY(Transient)
	UMoveHUD* MoveHUD;

	UPROPERTY(Transient)
	TArray<UMove*> Moves;

	int32 MoveCounter = 1;
	
	void SetCheckMate() const;

	void UndoLastMove();

public:

	// Set check in the last move
	void SetCheck() const;

	// Set result of the game
	void AddResult(bool HumanPlayer) const;

	// Set stalemate in the last move
	void AddStaleMate() const;

	// Add move to the list of moves
	void AddMove(UMove* Move);

	// Set the move HUD
	void SetMoveHud(UMoveHUD* MoveHud);

	// Set the error message
	void SetErrorMessage(const FString& Message) const;

	// Hide the error message
	void HiddenErrorMessage() const;

	// Convert Y to char
	static char GetYInChar(const int32 Y);

	// Get the name of the piece
	static FString GetNameOfPiece(APiece* Piece);

	// Check if other pieces (of the same player and same type) can go to the tile
	char FixIfOtherPieceCanGoToTile(ATile* OriginTile, ATile* DestinationTile, APiece* Piece) const;

	// Undo the moves
	void UndoTillMove(const int32 MoveIndex);
	
};


