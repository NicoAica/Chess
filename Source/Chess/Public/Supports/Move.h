// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile/Tile.h"
#include "Move.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMove : public UObject
{

	GENERATED_BODY()
	
public:
	UMove();

	// Constructor
	UMove(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece = nullptr, APiece* InPromotedPiece = nullptr);

	// Initialize the move
	void Initialize(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece = nullptr, APiece* InPromotedPiece = nullptr);

	// Set the piece promoted
	void SetPromotedPiece(APiece* InPromotedPiece);

	// Set the piece from promoted piece
	void SetPieceFromPromotedPiece();

	UPROPERTY(Transient)
	ATile* Origin;

	UPROPERTY(Transient)
	ATile* Destination;

	UPROPERTY(Transient)
	APiece* Piece;
	
	UPROPERTY(Transient)
	APiece* EatenPiece;
	
	UPROPERTY(Transient)
	APiece* PromotedPiece;
	
	bool Eat;
};
