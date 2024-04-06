// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
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

public:

	void SetCheck() const;

	void AddResult(bool HumanPlayer) const;

	void AddStaleMate() const;
	
	void AddMove(UMove* Move);

	void SetMoveHud(UMoveHUD* MoveHud);
	
	static char GetYInChar(const int32 Y);

	static FString GetNameOfPiece(APiece* Piece);

	// Check if other pieces (of the same player and same type) can go to the tile
	char FixIfOtherPieceCanGoToTile(ATile* OriginTile, ATile* DestinationTile, APiece* Piece) const;

	void UndoTillMove(const int32 MoveIndex);
	
};


