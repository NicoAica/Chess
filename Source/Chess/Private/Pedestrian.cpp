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
	//GMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
}

void APedestrian::CalculatePossibleMoveAndColorTile()
{
	FVector2D Position = ActualTile->GetGridPosition();

	PossibleMove.Empty();

	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();
	
	// If is Human Player
	if (ActualTile->GetOwner() == 0)
	{
		Position.X += 1;
		
		if (ATile** Tile = TileMap.Find(Position))
		{
			if ((*Tile)->GetTileStatus() == Empty)
			{
				(*Tile)->PossibleMoveColor();
				PossibleMove.Add(Position, *Tile);
				if ((*Tile)->GetTileStatus() != Occupied && Position.X == 2)
				{
					Position.X += 1;
					if (ATile** Tile2 = TileMap.Find(Position))
					{
						if ((*Tile2)->GetTileStatus() == Empty)
						{
							PossibleMove.Add(Position, *Tile);
							(*Tile2)->PossibleMoveColor();
						}
					}
					Position.X -= 1;
				}
			}
		}

		Position.Y -= 1;
		
		if (ATile** Tile = TileMap.Find(Position))
		{
			if ((*Tile)->GetOwner() == 1)
			{
				PossibleMove.Add(Position, *Tile);
				//UE_LOG(LogTemp, Error, TEXT("%s"), *(*Tile)->GetGridPosition().ToString());
				(*Tile)->PossibleMoveColor();
			}
		}

		Position.Y += 2;

		if (ATile** Tile = TileMap.Find(Position))
		{
			if ((*Tile)->GetOwner() == 1)
			{
				PossibleMove.Add(Position, *Tile);
				(*Tile)->PossibleMoveColor();
			}
		}
		
	}
}

bool APedestrian::CanGoTo(FVector2D Position)
{
	FVector2D ActualPosition = ActualTile->GetGridPosition();

	if (PossibleMove.Find(Position))
	{
		return true;
	}
	return false;
}



