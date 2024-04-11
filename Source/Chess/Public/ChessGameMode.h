// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameField.h"
#include "PlayerInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Supports/Move.h"
#include "ChessGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	// tracks if the game is over
	bool IsGameOver;
	
	// array of player interfaces
	TArray<IPlayerInterface*> Players;

	// tracks the current player index
	int32 CurrentPlayer;

	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameField> GameFieldClass;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere)
	AGameField* GField;

	AChessGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// get the next player index
	int32 GetNextPlayer(int32 Player) const;

	// called at the end of the game turn
	void TurnNextPlayer(UMove* Move);

	// called when the game begins
	void StartGame();

	// Called from Hud to choose player
	UFUNCTION(BlueprintCallable)
	void ChooseAiPlayerAndStartGame(bool IsMinMaxPlayer);
	
};
