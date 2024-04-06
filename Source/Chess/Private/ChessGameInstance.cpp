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
		
	MoveCounter++;
}

void UChessGameInstance::SetMoveHud(UMoveHUD* MoveHud)
{
	MoveHUD = MoveHud;
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
}
