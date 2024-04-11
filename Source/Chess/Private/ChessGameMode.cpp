// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"

#include "ChessGameInstance.h"
#include "EngineUtils.h"
#include "Players/HumanPlayer.h"
#include "Players/MinMaxPlayer.h"
#include "Players/RandomPlayer.h"

AChessGameMode::AChessGameMode(): IsGameOver(false), CurrentPlayer(0), GField(nullptr)
{
	// Set Project settings
	PlayerControllerClass = APlayerController::StaticClass();
	DefaultPawnClass = AHumanPlayer::StaticClass();
}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	AHumanPlayer* HumanPlayer = Cast<AHumanPlayer>(*TActorIterator<AHumanPlayer>(GetWorld()));

	GField = GetWorld()->SpawnActor<AGameField>(GameFieldClass);
	
	const FVector CameraPos(420, 420, 1000.0f); // 420 = ((120 * (8 + ((8 - 1)) - (8 - 1))) / 2) - (120 / 2)
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	Players.Add(HumanPlayer);
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

void AChessGameMode::TurnNextPlayer(UMove* Move)
{
	// Remove possible move color
	GField->DefaultTileColor();
	
	const int32 ActualPlayer = CurrentPlayer;
	
	Cast<UChessGameInstance>(GetGameInstance())->AddMove(Move);
	
	CurrentPlayer = GetNextPlayer(CurrentPlayer);

	if (GField->IsCheck(ActualPlayer))
	{
		if (GField->IsCheckMate(CurrentPlayer))
		{
			IsGameOver = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Check Mate!"));
			Cast<UChessGameInstance>(GetGameInstance())->AddResult(static_cast<bool>(CurrentPlayer));
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Check!"));
		Cast<UChessGameInstance>(GetGameInstance())->SetCheck();
	}
	else
	{
		if (GField->IsStaleMate(CurrentPlayer))
		{
			Cast<UChessGameInstance>(GetGameInstance())->AddStaleMate();
			IsGameOver = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Stale Mate!"));
			return;
		}
	}
		
	Players[CurrentPlayer]->OnTurn();
}

void AChessGameMode::StartGame()
{
	CurrentPlayer = 0;

	for (int32 i = 0; i < Players.Num(); i++)
	{
		Players[i]->PlayerNumber = i;
	}


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

void AChessGameMode::ChooseAiPlayerAndStartGame(bool IsMinMaxPlayer)
{
	if (IsMinMaxPlayer)
	{
		auto* AI = GetWorld()->SpawnActor<AMinMaxPlayer>(FVector(), FRotator());
		Players.Add(AI);
	}
	else
	{
		auto* AI = GetWorld()->SpawnActor<ARandomPlayer>(FVector(), FRotator());
		Players.Add(AI);
	}
	StartGame();
}
