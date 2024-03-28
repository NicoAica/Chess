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

int32 ABishop::CalculatePossibleMove()
{

	PossibleMove.Empty();

	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();
	
	ATile* Tmp = ActualTile;
	
	// Check on oblique top - right
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X += 1;
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

	// Check on oblique top - left
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X += 1;
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
	
	// Check on oblique bottom - left
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X -= 1;
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

	// Check on oblique bottom - right
	Tmp = ActualTile;
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X -= 1;
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
	
	return PossibleMove.Num();
}
