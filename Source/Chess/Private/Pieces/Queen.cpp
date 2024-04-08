// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/Queen.h"

#include "ChessGameMode.h"

AQueen::AQueen()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AQueen::BeginPlay()
{
	Super::BeginPlay();
}

int32 AQueen::CalculatePossibleMove(const bool CheckScacco)
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

	// Check on top
	CalculatePossibleMoveInDirection(1, 0, CheckScacco);

	// Check on bottom
	CalculatePossibleMoveInDirection(-1, 0, CheckScacco);

	// Check on right
	CalculatePossibleMoveInDirection(0, 1, CheckScacco);

	// Check on left
	CalculatePossibleMoveInDirection(0, -1, CheckScacco);
	
	return PossibleMove.Num();
}

