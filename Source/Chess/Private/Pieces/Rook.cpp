// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/Rook.h"

#include "ChessGameMode.h"

ARook::ARook()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARook::BeginPlay()
{
	Super::BeginPlay();
}

int32 ARook::CalculatePossibleMove(const bool CheckScacco)
{

	PossibleMove.Empty();

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
