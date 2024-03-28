// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Bishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ABishop : public APiece
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABishop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual int32 CalculatePossibleMove() override;
	
};
