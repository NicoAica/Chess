// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/Bishop.h"

#include "ChessGameMode.h"

ABishop::ABishop()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABishop::BeginPlay()
{
	Super::BeginPlay();
}

int32 ABishop::CalculatePossibleMove(const bool CheckScacco)
{

	PossibleMove.Empty();

	// Check on oblique top - Right
	CalculatePossibleMoveInDirection(1, 1, CheckScacco);

	// Check on oblique top - Left
	CalculatePossibleMoveInDirection(1, -1, CheckScacco);

	// Check on oblique bottom - Right
	CalculatePossibleMoveInDirection(-1, 1, CheckScacco);

	// Check on oblique bottom - left
	CalculatePossibleMoveInDirection(-1, -1, CheckScacco);
	
	return PossibleMove.Num();
}
