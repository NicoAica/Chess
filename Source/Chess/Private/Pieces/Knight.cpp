// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/Knight.h"

#include "ChessGameMode.h"

AKnight::AKnight()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AKnight::BeginPlay()
{
	Super::BeginPlay();
}

int32 AKnight::CalculatePossibleMove(const bool CheckScacco)
{

	PossibleMove.Empty();

	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();

	FVector2D const Position = ActualTile->GetGridPosition();
	TArray<FVector2D> PossiblePositionAvailable;
	
	PossiblePositionAvailable.Add(FVector2D(Position.X + 2, Position.Y - 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X + 2, Position.Y + 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X + 1, Position.Y - 2));
	PossiblePositionAvailable.Add(FVector2D(Position.X + 1, Position.Y + 2));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 1, Position.Y - 2));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 1, Position.Y + 2));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 2, Position.Y - 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 2, Position.Y + 1));
	
	for (FVector2D NewPosition: PossiblePositionAvailable)
	{
		if (ATile** NewTile = TileMap.Find(NewPosition); NewTile != nullptr && *NewTile != nullptr)
		{
			if ((*NewTile)->GetTileStatus() != Occupied)
			{
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				}
			}
		}
	}
	
	return PossibleMove.Num();
}
