// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Rook.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ARook : public APiece
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ARook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual int32 CalculatePossibleMove(const bool CheckScacco = true) override;
	
};
