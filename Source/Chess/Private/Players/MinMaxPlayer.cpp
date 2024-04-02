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

	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	{
		MoveActorTo(NextMove->Destination, NextMove->Piece, NextMove->Eat);
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer();
	}, 3.0f, false);
	
	
}

void AMinMaxPlayer::MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool Eat) const
{
	if (Eat)
	{
		FutureTile->GetPiece()->SelfDestroy();
	}
	
	/* Promote */
	if (FutureTile->GetGridPosition().X == 0 && Cast<APedestrian>(SelectedPiece))
	{
		UE_LOG(LogTemp, Error, TEXT("Promozione"));
		
		// Remove reference
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		
		// Spawn queen
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->Promote(FutureTile, 1);

		SelectedPiece->SelfDestroy();
		
	}
	else
	{
		// Calc future location
		const FVector2D FutureTilePosition = FutureTile->GetGridPosition();
		FVector const FuturePosition = FVector(FutureTilePosition.X * 120, FutureTilePosition.Y * 120, SelectedPiece->GetActorLocation().Z);
	
		// Move Actor
		SelectedPiece->SetActorLocation(FuturePosition);

		// Change Tile Info
		FutureTile->SetTileStatus(1, Occupied, SelectedPiece->GetActualTile()->B_IsKingTile);
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		SelectedPiece->SetActualTile(FutureTile);
		FutureTile->SetPiece(SelectedPiece);
	}
	
	// Remove possible move color
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->DefaultTileColor();
}

int32 AMinMaxPlayer::MinMax(int Depth, bool IsMaximizingPlayer)
{
	if (Depth > Difficulty)
	{
		return Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->ValueOfChessBoard();
	}
	
	if (IsMaximizingPlayer)
	{
		// min value possible
		int Max = -39;

		FMove* Move = new FMove();

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
				
				/*if (Tile->GetOwner() == 0)
				{
					IsSafe = !Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(1);
				}
				else
				{
					IsSafe = !Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(0);
				}*/

				int32 ChessBoardValue = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->ValueOfChessBoard();
				
				//UE_LOG(LogTemp, Warning, TEXT("Value of chess board: %d"), ChessBoardValue);

				int32 Min = MinMax(Depth + 1, false);
				
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
					Move = new FMove(OldTile, Tile, Piece, B_IsOccupied);
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

	FMove* Move = new FMove();

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
				
			/*if (Tile->GetOwner() == 0)
				{
					IsSafe = !Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(1);
				}
				else
				{
					IsSafe = !Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->IsCheck(0);
				}*/

			//UE_LOG(LogTemp, Warning, TEXT("Value of chess board: %d"), Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->ValueOfChessBoard());

			int32 Max = MinMax(Depth + 1, true);
		
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
				Move = new FMove(OldTile, Tile, Piece, B_IsOccupied);
			}
				
			++It2;
		}
		++It;
	}
	NextMove = Move;
	return Min;
}


