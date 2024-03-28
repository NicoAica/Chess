// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterface.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UCLASS()
class CHESS_API APiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece();
	
	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* Scene;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	IPlayerInterface *PlayerOwner;

	// Keep in witch tile is
	UPROPERTY()
	ATile* ActualTile = nullptr;

	UPROPERTY()
	TMap<FVector2D, ATile*> PossibleMove;

public:

	void SetPlayerOwner(IPlayerInterface *Player);

	UFUNCTION()
	void SelfDestroy();

	void SetActualTile(ATile* Tile);
	
	ATile* GetActualTile() const;


	// Use this method to color the tile
	void ColorTilePossibleMove();
	
	// Use this method to calculate possible move
	virtual int32 CalculatePossibleMove() { return 0; }

	// Use this method to know if is a valid move (not safe move)
	bool CanGoTo(FVector2D Position);

	// Use this method to get random available position
	ATile* GetRandomAvailableTile();
	
};
