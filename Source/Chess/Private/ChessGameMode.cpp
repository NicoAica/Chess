// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"
#include "EngineUtils.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"

AChessGameMode::AChessGameMode()
{
	// Set Project settings
	PlayerControllerClass = APlayerController::StaticClass();
	DefaultPawnClass = AHumanPlayer::StaticClass();
	
}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	// TODO Edit
	MoveCounter = 0;

	AHumanPlayer* HumanPlayer = Cast<AHumanPlayer>(*TActorIterator<AHumanPlayer>(GetWorld()));

	if (GameFieldClass != nullptr)
	{
		GField = GetWorld()->SpawnActor<AGameField>(GameFieldClass);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	float CameraPosX = ((120 * (8 + ((8 - 1)) - (8 - 1))) / 2) - (120 / 2);
	FVector CameraPos(CameraPosX, CameraPosX, 1000.0f);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());
	
	// Human player = 0
	Players.Add(HumanPlayer);
	// Random Player
	ARandomPlayer* AI = GetWorld()->SpawnActor<ARandomPlayer>(FVector(), FRotator());

	// MiniMax Player
	//auto* AI = GetWorld()->SpawnActor<ATTT_MinimaxPlayer>(FVector(), FRotator());

	// AI player = 1
	Players.Add(AI);

	this->ChoosePlayerAndStartGame();
}

void AChessGameMode::SetCellPawn(const int32 PlayerNumber, const FVector& SpawnPosition)
{
	if (IsGameOver)
	{
		return;
	}

	// Destination cell


	// Is win position

	// else next player 
	
}

int32 AChessGameMode::GetNextPlayer(int32 Player) const
{
	Player++;
	if (!Players.IsValidIndex(Player))
	{
		Player = 0;
	}
	return Player;
}

void AChessGameMode::TurnNextPlayer()
{
	UE_LOG(LogTemp, Error, TEXT("Player %d, do Check: %hhd"), CurrentPlayer, GField->DoCheck(CurrentPlayer));
	MoveCounter += 1;
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	Players[CurrentPlayer]->OnTurn();
}

void AChessGameMode::ChoosePlayerAndStartGame()
{
	CurrentPlayer = 0;

	for (int32 i = 0; i < Players.Num(); i++)
	{
		Players[i]->PlayerNumber = i;
	}
	MoveCounter += 1;

	for (int32 i = 0; i < Players.Num(); i++)
	{
		TMap<FVector2D, ATile*> Tmp;
		GField->GetYourTile(i, Tmp);

		auto It = Tmp.CreateIterator();
		while (It)
		{
			It.Value()->GetPiece()->CalculatePossibleMove(false);
			++It;
		}
	}
	
	Players[CurrentPlayer]->OnTurn();
}