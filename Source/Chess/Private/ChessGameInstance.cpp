// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameInstance.h"

#include "ChessGameMode.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Pedestrian.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"

void UChessGameInstance::SetCheck() const
{
	MoveHUD->AddCheckInLastMove();	
}

void UChessGameInstance::SetCheckMate() const
{
	MoveHUD->AddCheckMateInLastMove();
}


void UChessGameInstance::AddResult(bool const HumanPlayer) const
{
	SetCheckMate();
	if (HumanPlayer)
	{
		MoveHUD->AddInList("1-0");
	}
	else
	{
		MoveHUD->AddInList("0-1");
	}
}

void UChessGameInstance::AddStaleMate() const
{
	MoveHUD->AddInList("1/2 - 1/2");
}


void UChessGameInstance::AddMove(UMove* Move)
{
	Moves.Add(Move);
	
	MoveHUD->AddInList(
		FString::FromInt(MoveCounter) +
		". " + GetNameOfPiece(Move->Piece) +
		FixIfOtherPieceCanGoToTile(Move->Origin, Move->Destination, Move->Piece) +
		(Move->Eat ? "x" : "") +
		GetYInChar(Move->Destination->GetGridPosition().Y) +
		FString::FromInt(Move->Destination->GetGridPosition().X + 1),
		Move->Destination->GetOwner() == 0,
		MoveCounter
		);

	//UE_LOG(LogTemp, Error, TEXT("Piece moved from Position: %s, piece eaten: %s"), *Move->Origin->GetActorLocation().ToString(), Move->EatenPiece ? *Move->EatenPiece->GetName() : TEXT("None"));
	
	MoveCounter++;
}

void UChessGameInstance::SetMoveHud(UMoveHUD* MoveHud)
{
	MoveHUD = MoveHud;
}

void UChessGameInstance::SetErrorMessage(const FString& Message) const
{
	MoveHUD->SetErrorMessage(Message);
}

void UChessGameInstance::HiddenErrorMessage() const
{
	MoveHUD->HiddenErrorMessage();
}

char UChessGameInstance::GetYInChar(const int32 Y)
{
	return static_cast<char>(Y + 97);
}

FString UChessGameInstance::GetNameOfPiece(APiece* Piece)
{
	if (Cast<APedestrian>(Piece))
	{
		return " ";
	}
	if (Cast<ABishop>(Piece))
	{
		return "B";
	}
	if (Cast<AKnight>(Piece))
	{
		return "N";
	}
	if (Cast<ARook>(Piece))
	{
		return "R";
	}
	if (Cast<AQueen>(Piece))
	{
		return "Q";
	}
	return "K";
}

char UChessGameInstance::FixIfOtherPieceCanGoToTile(ATile* OriginTile, ATile* DestinationTile, APiece* Piece) const
{
	TMap<FVector2D, ATile*> MyTile;
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->GetYourTile(DestinationTile->GetOwner(), MyTile);

	for (auto const& Elem : MyTile)
	{
		APiece* const P = Elem.Value->GetPiece();
		if ((P != Piece) && (GetNameOfPiece(P) == GetNameOfPiece(Piece)) && (P->PossibleMove.Find(DestinationTile->GetGridPosition()) != nullptr))
		{
			if (P->GetActualTile()->GetGridPosition().Y == OriginTile->GetGridPosition().Y)
			{
				return static_cast<char>(OriginTile->GetGridPosition().X + 49);
			}
			return GetYInChar(OriginTile->GetGridPosition().Y);
		}
	}
	return 0;
}

void UChessGameInstance::UndoTillMove(const int32 MoveIndex)
{
	UE_LOG(LogTemp, Error, TEXT("UndoMoves %d"), MoveIndex);

	while (MoveCounter > MoveIndex)
	{
		MoveCounter--;
		MoveHUD->PopLastMove();
		UndoLastMove();
	}
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->DefaultTileColor();
}

void UChessGameInstance::UndoLastMove()
{
	UMove* Move = Moves.Pop();
	
	// Calc future location (in old position)
	const FVector2D OldTilePosition = Move->Origin->GetGridPosition();
	FVector const OldPosition = FVector(OldTilePosition.X * 120, OldTilePosition.Y * 120, Move->Piece->GetActorLocation().Z);
	
	// Set Original Piece (Promote Exception)
	if (Move->PromotedPiece != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Promoted Piece"));
		Move->SetPieceFromPromotedPiece();
	}

	// Move Actor
	Move->Piece->SetActorLocation(OldPosition);

	// Set Origin Tile
	Move->Piece->SetActualTile(Move->Origin);
	Move->Origin->SetTileStatus((Moves.Num() % 2 == 0? 0 : 1), Occupied, Move->Destination->B_IsKingTile);
	Move->Origin->SetPiece(Move->Piece);
	
	// Set Destination Tile
	if (Move->Eat)
	{
		Move->EatenPiece->SelfRespawn();
		Move->EatenPiece->SetActualTile(Move->Destination);
		Move->Destination->SetPiece(Move->EatenPiece);
		Move->Destination->SetTileStatus((Moves.Num() % 2 == 0? 1 : 0), Occupied, false);

		Move->EatenPiece->CalculatePossibleMove(true);
	}
	else
	{
		Move->Destination->SetPiece(nullptr);
		Move->Destination->SetTileStatus(-1, Empty, false);
	}

	Move->Piece->CalculatePossibleMove(true);
	
}
