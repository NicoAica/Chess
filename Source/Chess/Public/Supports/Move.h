// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"

/**
 * 
 */
class CHESS_API FMove 
{
public:
	FMove();
	~FMove();

	FMove(ATile* Origin, ATile* Destination, APiece* Piece, bool Eat);
	
	ATile* Origin;
	ATile* Destination;
	APiece* Piece;
	bool Eat;
};
