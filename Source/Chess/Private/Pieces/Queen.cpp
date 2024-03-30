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

	//AGameField *GField = Cast<AGameField>(GetWorld()->GetAuthGameMode());

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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				}
				Tmp = nullptr;
			}
		}
		else
		{
			Tmp = nullptr;
		}
	}

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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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
				AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
				Tmp = (*NewTile);
			}
			else
			{
				if ((*NewTile)->GetOwner() != ActualTile->GetOwner())
				{
					AddPossibleMove(NewPosition, (*NewTile), this, CheckScacco);
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

