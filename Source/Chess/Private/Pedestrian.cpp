// Fill out your copyright notice in the Description page of Project Settings.


#include "Pedestrian.h"
#include "ChessGameMode.h"

// Sets default values
APedestrian::APedestrian()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APedestrian::BeginPlay()
{
	Super::BeginPlay();
}

int32 APedestrian::CalculatePossibleMoveAndColorTile()
{
	FVector2D Position = ActualTile->GetGridPosition();

	PossibleMove.Empty();

	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();

	ActualTile->GetOwner() == 0 ? Position.X += 1 : Position.X -= 1;

	if (ATile** Tile = TileMap.Find(Position))
	{
		if ((*Tile)->GetTileStatus() == Empty)
		{
			(*Tile)->PossibleMoveColor();
			PossibleMove.Add(Position, *Tile);
			
			if ((*Tile)->GetTileStatus() != Occupied && Position.X == (ActualTile->GetOwner() == 0 ? 2 : 5))
			{
				ActualTile->GetOwner() == 0 ? Position.X += 1 : Position.X -= 1;
				if (ATile** Tile2 = TileMap.Find(Position))
				{
					if ((*Tile2)->GetTileStatus() == Empty)
					{
						PossibleMove.Add(Position, *Tile);
						(*Tile2)->PossibleMoveColor();
					}
				}
				ActualTile->GetOwner() == 0 ? Position.X -= 1 : Position.X += 1;
			}
		}
	}
 
	Position.Y -= 1;

	if (ATile** Tile = TileMap.Find(Position))
	{
		if ((*Tile)->GetTileStatus() != Empty && (*Tile)->GetOwner() != ActualTile->GetOwner())
		{
			PossibleMove.Add(Position, *Tile);
			//UE_LOG(LogTemp, Error, TEXT("%s"), *(*Tile)->GetGridPosition().ToString());
			(*Tile)->PossibleMoveColor();
		}
	}

	Position.Y += 2;

	if (ATile** Tile = TileMap.Find(Position))
	{
		if ((*Tile)->GetTileStatus() != Empty && (*Tile)->GetOwner() != ActualTile->GetOwner())
		{
			PossibleMove.Add(Position, *Tile);
			(*Tile)->PossibleMoveColor();
		}
	}

	return PossibleMove.Num();
}

bool APedestrian::CanGoTo(FVector2D Position)
{
	if (PossibleMove.Find(Position))
	{
		return true;
	}
	return false;
}

ATile* APedestrian::GetRandomAvailableTile()
{
	auto It = PossibleMove.CreateIterator();
	if (!PossibleMove.Num()) return nullptr;
	int32 const Rand = rand() % PossibleMove.Num();
	for (int32 i = 0; i < Rand; i++)
		++It;
	return It->Value;
}
