// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Players/PlayerInterface.h"
#include "Tile/Tile.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UCLASS()
class CHESS_API APiece : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* Scene;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	IPlayerInterface *PlayerOwner;

	// Keep in witch tile is
	UPROPERTY(VisibleAnywhere)
	ATile* ActualTile = nullptr;

	void CalculatePossibleMoveInDirection(int32 X, int32 Y, const bool CheckScacco = true);

public:

	// Sets default values for this actor's properties
	APiece();
	
	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	TMap<FVector2D, ATile*> PossibleMove;

	void SetPlayerOwner(IPlayerInterface *Player);
	
	void SelfDestroy();
	
	void HardDestroy();

	void SelfRespawn();

	void SetActualTile(ATile* Tile);
	
	ATile* GetActualTile() const;


	// Use this method to color the tile
	void ColorTilePossibleMove();
	
	// Use this method to calculate possible move
	virtual int32 CalculatePossibleMove(const bool CheckScacco = true) { return 0; }

	void AddPossibleMove(FVector2D Position, ATile* Tile, APiece* Piece, bool CheckScacco = true);

	// Use this method to know if is a valid move (not safe move)
	bool CanGoTo(FVector2D Position);

	// Use this method to get random available position
	ATile* GetRandomAvailableTile();
	
};
