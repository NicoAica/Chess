// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ChessGameMode.h"
#include "Piece.h"
#include "GameFramework/Actor.h"
#include "Pedestrian.generated.h"


UCLASS()
class CHESS_API APedestrian : public APiece
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APedestrian();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual int32 CalculatePossibleMoveAndColorTile() override;

	virtual bool CanGoTo(FVector2D Position) override;

	virtual ATile* GetRandomAvailableTile() override;

};

