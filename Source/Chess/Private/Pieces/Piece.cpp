// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/Piece.h"

#include "ChessGameMode.h"

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PlayerOwner = nullptr;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
}

void APiece::CalculatePossibleMoveInDirection(const int32 X, const int32 Y, const bool CheckScacco)
{
	TMap<FVector2D, ATile*> TileMap = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetTileMap();
	
	ATile* Tmp = ActualTile;
	
	while (Tmp != nullptr)
	{
		FVector2D NewPosition = Tmp->GetGridPosition();
		NewPosition.X += X;
		NewPosition.Y += Y;
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
}

void APiece::SetPlayerOwner(IPlayerInterface *Player)
{
	PlayerOwner = Player;
}

void APiece::SelfDestroy()
{
	//Destroy(); Choose to not destroy the piece to implement undo function in easy way
	FVector FuturePosition = GetActorLocation();
	FuturePosition.Z = -100;
	this->SetActorLocation(FuturePosition);
}

void APiece::HardDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy"));
	Destroy();
}

void APiece::SelfRespawn()
{
	if (this->IsValidLowLevel()) {
		FVector FuturePosition = GetActorLocation();
		FuturePosition.Z = 4.5;
		this->SetActorLocation(FuturePosition);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Actor is not valid."));
	}
}

void APiece::SetActualTile(ATile* Tile)
{
	ActualTile = Tile;
}

ATile* APiece::GetActualTile() const
{
	return ActualTile;
}

void APiece::ColorTilePossibleMove()
{
	auto It = PossibleMove.CreateIterator();
	while (It)
	{
		It->Value->PossibleMoveColor();
		++It;
	}
}

void APiece::AddPossibleMove(const FVector2D Position, ATile* Tile, APiece* Piece, const bool CheckScacco)
{
	if (CheckScacco)
	{
		ATile* OldTile = Piece->GetActualTile();

		bool B_IsOccupied = false;
		bool B_IsKing = false;
		APiece* PieceOnTile = nullptr;
		int32 FutureTileOwner = -1;

		bool IsSafe;
		
		if (Tile->GetTileStatus() != Empty) 
		{
			PieceOnTile = Tile->GetPiece();
			FutureTileOwner = Tile->GetOwner();
			B_IsOccupied = true;
			B_IsKing = Tile->B_IsKingTile;
		}
		
		Tile->SetTileStatus(OldTile->GetOwner(), Occupied, OldTile->B_IsKingTile);
		Tile->SetPiece(Piece);
		Piece->SetActualTile(Tile);
		
		OldTile->SetTileStatus(-1, Empty, false);
		OldTile->SetPiece(nullptr);
		
		
		if (Tile->GetOwner() == 0)
		{
			IsSafe = !Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(1);
		}
		else
		{
			IsSafe = !Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(0);
		}
		
		OldTile->SetTileStatus(Tile->GetOwner(), Occupied, Tile->B_IsKingTile);
		OldTile->SetPiece(Tile->GetPiece());
		Piece->SetActualTile(OldTile);

		Tile->SetTileStatus(-1, Empty, false);
		Tile->SetPiece(PieceOnTile);

		if (B_IsOccupied)
		{
			Tile->SetTileStatus(FutureTileOwner, Occupied, B_IsKing);
			PieceOnTile->SetActualTile(Tile);
		}

		if (IsSafe)
		{
			PossibleMove.Add(Position, Tile);
		}
	}
	else
	{
		PossibleMove.Add(Position, Tile);
	}
}

bool APiece::CanGoTo(FVector2D const Position)
{
	if (PossibleMove.Find(Position))
	{
		return true;
	}
	return false;
}

ATile* APiece::GetRandomAvailableTile()
{
	auto It = PossibleMove.CreateIterator();
	if (!PossibleMove.Num()) return nullptr;
	int32 const Rand = rand() % PossibleMove.Num();
	for (int32 i = 0; i < Rand; i++)
		++It;
	return It->Value;
}

