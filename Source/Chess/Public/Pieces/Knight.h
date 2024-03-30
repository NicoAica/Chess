// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Knight.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AKnight : public APiece
{
	GENERATED_BODY()

	AKnight();

public:
	
	virtual void BeginPlay() override;

	virtual int32 CalculatePossibleMove(const bool CheckScacco = true) override;
	
};
