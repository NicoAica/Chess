// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HUD/MoveHUD.h"
#include "Supports/Move.h"
#include "ChessGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessGameInstance : public UGameInstance
{
	GENERATED_BODY()

	FString LastMove;

	UPROPERTY(Transient)
	UMoveHUD* MoveHUD;

	//UPROPERTY(Transient)
	//TArray<FMove> Moves;

public:
	
	int32 MoveCounter = 0;


	FString GetLastMove()
	{
		return LastMove;
	}

	void SetLastMove(FMove*  Move)
	{
		if (MoveHUD == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveHUD is nullptr"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("DAGLIE MoveHUD is not nullptr"));
			MoveHUD->Test(FString("Test ") + FString::FromInt(MoveCounter) + FString(" "));
		}
		MoveCounter++;
//		LastMove = Move;
	}

	void SetMoveHud(UMoveHUD* MoveHud);
	
	
};
