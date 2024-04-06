// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
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

	UMove(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece = nullptr);

	void Initialize(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece = nullptr);

	UPROPERTY(Transient)
	ATile* Origin;

	UPROPERTY(Transient)
	ATile* Destination;

	UPROPERTY(Transient)
	APiece* Piece;

	UPROPERTY(Transient)
	APiece* EatenPiece;
	
	bool Eat;
};
