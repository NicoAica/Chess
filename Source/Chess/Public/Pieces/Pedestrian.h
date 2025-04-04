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

	virtual int32 CalculatePossibleMove(const bool CheckScacco = true) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

