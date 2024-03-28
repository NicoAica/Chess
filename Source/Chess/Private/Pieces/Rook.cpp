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

int32 ARook::CalculatePossibleMove()
{

	PossibleMove.Empty();

	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();
	
	// Check on horizontal right
	ATile* Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.Y += 1;
		if (ATile** NewTile = TileMap.Find(NewPosition); NewTile != nullptr && *NewTile != nullptr)
		{
			if ((*NewTile)->GetTileStatus() != Occupied)
			{
				PossibleMove.Add(NewPosition, (*NewTile));
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					PossibleMove.Add(NewPosition, (*NewTile));
				}
				Tmp = nullptr;
			}
		}
		else
		{
			Tmp = nullptr;
		}
	}

	// Check on horizontal left
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.Y -= 1;
		if (ATile** NewTile = TileMap.Find(NewPosition); NewTile != nullptr && *NewTile != nullptr)
		{
			if ((*NewTile)->GetTileStatus() != Occupied)
			{
				PossibleMove.Add(NewPosition, (*NewTile));
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					PossibleMove.Add(NewPosition, (*NewTile));
				}
				Tmp = nullptr;
			}
		}
		else
		{
			Tmp = nullptr;
		}
	}

	// Check on vertical top
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X += 1;
		if (ATile** NewTile = TileMap.Find(NewPosition); NewTile != nullptr && *NewTile != nullptr)
		{
			if ((*NewTile)->GetTileStatus() != Occupied)
			{
				PossibleMove.Add(NewPosition, (*NewTile));
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					PossibleMove.Add(NewPosition, (*NewTile));
				}
				Tmp = nullptr;
			}
		}
		else
		{
			Tmp = nullptr;
		}
	}

	// Check on vertical bottom
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X -= 1;
		if (ATile** NewTile = TileMap.Find(NewPosition); NewTile != nullptr && *NewTile != nullptr)
		{
			if ((*NewTile)->GetTileStatus() != Occupied)
			{
				PossibleMove.Add(NewPosition, (*NewTile));
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					PossibleMove.Add(NewPosition, (*NewTile));
				}
				Tmp = nullptr;
			}
		}
		else
		{
			Tmp = nullptr;
		}
	}
	
	return PossibleMove.Num();
}
