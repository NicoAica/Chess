// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Queen.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AQueen : public APiece
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQueen();

	virtual int32 CalculatePossibleMove(const bool CheckScacco = true) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
