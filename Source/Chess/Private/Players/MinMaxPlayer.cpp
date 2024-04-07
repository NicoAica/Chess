// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MinMaxPlayer.h"

#include "ChessGameMode.h"

// Sets default values
AMinMaxPlayer::AMinMaxPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMinMaxPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void AMinMaxPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinMaxPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI MinMax Turn"));
	auto const GField = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField;

	
	int32 _MinMax = MinMax(0, false);
	UE_LOG(LogTemp, Warning, TEXT("Best value: %d"), _MinMax);

	NextMove->Piece->CalculatePossibleMove();
	NextMove->Piece->ColorTilePossibleMove();

	auto GMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this, GMode]()
	{
		UMove *Move = NewObject<UMove>();
		Move->Initialize(NextMove->Origin, NextMove->Destination, NextMove->Piece, NextMove->Eat, NextMove->EatenPiece);

		bool const B_IsPromotionMove = NextMove->Destination->GetGridPosition().X == 0 && Cast<APedestrian>(NextMove->Piece);	
		
		GMode->GField->MoveActorTo(NextMove->Destination, NextMove->Piece, NextMove->Eat, 1);
		
		if (B_IsPromotionMove)
		{
			Move->SetPromotedPiece(NextMove->Destination->GetPiece());
		}
		
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer(Move);

	}, 1.0f, false);
	
}

int32 AMinMaxPlayer::MinMax(int Depth, bool IsMaximizingPlayer)
{
	if (Depth > Difficulty)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Value of chess board: %d"), Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->ValueOfChessBoard());
		return Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->ValueOfChessBoard();
	}
	
	if (IsMaximizingPlayer)
	{
		// min value possible
		int Max = -39;

		UMove* Move = NewObject<UMove>();

		TMap<FVector2D, ATile*> WhitePieces;
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetYourTile(0, WhitePieces);

		auto It = WhitePieces.CreateIterator();
		while (It)
		{
			// Calculate possible moves of piece
			It->Value->GetPiece()->CalculatePossibleMove();
			
			// Get all possible moves of piece
			TMap<FVector2D, ATile*> PossibleMoves = It->Value->GetPiece()->PossibleMove;
			
			auto It2 = PossibleMoves.CreateIterator();
			while (It2)
			{
				// Move piece
				ATile* OldTile = It->Value;
				ATile* Tile = It2->Value;
				APiece* Piece = OldTile->GetPiece();
				
				bool B_IsOccupied = false;
				bool B_IsKing = false;
				APiece* PieceOnTile = nullptr;
				int32 FutureTileOwner = -1;
				
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
				
				
				//UE_LOG(LogTemp, Warning, TEXT("Value of chess board: %d"), ChessBoardValue);

				int32 Min;
				if (Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(0))
				{
					if (Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheckMate(1))
					{
						Min = 50;
					}
					else
					{
						// Assigned to check 1 points
						Min = MinMax(Depth + 1, true) + 1;
					}
				}
				else
				{
					Min = MinMax(Depth + 1, false);
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

				if (Min > Max)
				{
					Max = Min;
					Move->Initialize(OldTile, Tile, Piece, B_IsOccupied, PieceOnTile);
				}
				
				++It2;
			}
			++It;
		}
		
		NextMove = Move;
		return Max;
		
	}


	
	// max value possible
	int Min = 39;

	UMove* Move = NewObject<UMove>();

	TMap<FVector2D, ATile*> BlackPieces;
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetYourTile(1, BlackPieces);

	auto It = BlackPieces.CreateIterator();
	while (It)
	{
		// Calculate possible moves of piece
		It->Value->GetPiece()->CalculatePossibleMove();
		
		// Get all possible moves of piece
		TMap<FVector2D, ATile*> PossibleMoves = It->Value->GetPiece()->PossibleMove;
			
		auto It2 = PossibleMoves.CreateIterator();
		while (It2)
		{
			// Move piece
			ATile* OldTile = It->Value;
			ATile* Tile = It2->Value;
			APiece* Piece = OldTile->GetPiece();
				
			bool B_IsOccupied = false;
			bool B_IsKing = false;
			APiece* PieceOnTile = nullptr;
			int32 FutureTileOwner = -1;

			//bool IsSafe;
		
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

			int32 Max;
			
			if (Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(1))
			{
				if (Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheckMate(0))
				{
					Max = -50;
				}
				else
				{
					// Assigned to check 1 points
					Max = MinMax(Depth + 1, true);
					//UE_LOG(LogTemp, Warning, TEXT("Passo a volte qui dentro, Max: %d"), Max);
					Max -= 1;
				}
				//UE_LOG(LogTemp, Warning, TEXT("Passo a volte qui, Max: %d"), Max);
			}
			else
			{
				Max = MinMax(Depth + 1, true);
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
			if (Min > Max)
			{
				Min = Max;
				Move->Initialize(OldTile, Tile, Piece, B_IsOccupied, PieceOnTile);
			}
				
			++It2;
		}
		++It;
	}
	NextMove = Move;
	return Min;
}


