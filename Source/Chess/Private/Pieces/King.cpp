// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/King.h"

#include "ChessGameMode.h"

AKing::AKing()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKing::BeginPlay()
{
	Super::BeginPlay();
}

int32 AKing::CalculatePossibleMove()
{

	PossibleMove.Empty();

	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();

	FVector2D const Position = ActualTile->GetGridPosition();
	TArray<FVector2D> PossiblePositionAvailable;
	
	PossiblePositionAvailable.Add(FVector2D(Position.X + 1, Position.Y + 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X + 1, Position.Y));
	PossiblePositionAvailable.Add(FVector2D(Position.X + 1, Position.Y - 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X, Position.Y - 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 1, Position.Y - 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 1, Position.Y));
	PossiblePositionAvailable.Add(FVector2D(Position.X - 1, Position.Y + 1));
	PossiblePositionAvailable.Add(FVector2D(Position.X, Position.Y + 1));
	
	for (FVector2D NewPosition: PossiblePositionAvailable)
	{
		if (ATile** NewTile = TileMap.Find(NewPosition); NewTile != nullptr && *NewTile != nullptr)
		{
			if ((*NewTile)->GetTileStatus() != Occupied)
			{
				PossibleMove.Add(NewPosition, (*NewTile));
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					PossibleMove.Add(NewPosition, (*NewTile));
				}
			}
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Le sono: %d"), PossibleMove.Num())
	return PossibleMove.Num();
}