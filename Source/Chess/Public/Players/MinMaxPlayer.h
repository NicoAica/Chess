// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterface.h"
#include "Tile.h"
#include "GameFramework/Pawn.h"
#include "Supports/Move.h"
#include "MinMaxPlayer.generated.h"

UCLASS()
class CHESS_API AMinMaxPlayer : public APawn, public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinMaxPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Updated in MinMax, used in MoveActorTo
	UPROPERTY(Transient)
	UMove* NextMove;

	// Difficulty of AI (MinMax Depth)
	int32 Difficulty = 2;
	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnTurn() override;

	void MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool Eat) const;

	int32 MinMax(int Depth, bool IsMaximizingPlayer);

};




