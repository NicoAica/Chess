// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pieces/Pedestrian.h"
#include "Tile.h"
#include "GameFramework/Actor.h" 
#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "GameField.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset);

UCLASS()
class CHESS_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();
	
	//virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void ResetField();

	void GenerateField();

	static FVector2D GetPosition(const FHitResult& Hit);

	TArray<ATile*>& GetTileArray();

	TMap<FVector2D, ATile*>& GetTileMap();

	// Return only the tiles that belong to the player
	TMap<FVector2D, ATile*>& GetYourTile(const int32 Player, TMap<FVector2D, ATile*>& Tmp);

	// Return if the player make check
	bool IsCheck(const int32 Player);

	// Check if Player make a check
	bool IsCheckMate(const int32 Player);

	// Promote
	void Promote(ATile* FuturePosition, int32 Player);

	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	static FVector2D GetXYPositionByRelativeLocation(const FVector& Location);

	static bool IsWinPosition(const FVector2D Position);

	inline bool IsValidPosition(const FVector2D Begin, const FVector2D End) const;

	TArray<int32> GetLine(const FVector2D Begin, const FVector2D End);
	
	bool AllEqual(const TArray<int32>& Array) const;

	// Use this method to color the tile spawned to default
	void DefaultTileColor();

	// Propriety assigned in blueprint
	UPROPERTY(BlueprintAssignable)
	FOnReset OnResetEvent;

	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;

	// Return the number of black pieces
	int32 GetNumberOfBlackPiece();

	// Return the N-th cell with a black piece.
	ATile* GetTileOfBlackPiece(int32 N);

	/* Spawn Pieces */
	void SpawnPedestrianOnTiles();
	void SpawnQueensOnTile();
	void SpawnKnightsOnTile();
	void SpawnRooksOnTile();
	void SpawnBishopsOnTile();
	void SpawnKingsOnTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	TArray<ATile*> TileArray;

	static const int32 Not_Assigned = -1;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const int32 Size = 8;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//int32 WinSize;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	/* BluePrint Classes */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APedestrian> PedestrianClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AQueen> QueenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AKnight> KnightClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARook> RookClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABishop> BishopClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AKing> KingClass;

	/* Material Instance Configuration */
	// Tile
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceTileGreen;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceTileWhite;

	// Pieces
	// Pedestrian
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstancePedestrianWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstancePedestrianBlack;

	// Queens
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceQueenWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceQueenBlack;
	
	// Knight
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceKnightWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceKnightBlack;

	// Rook
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceRookWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceRookBlack;

	// Bishop
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceBishopWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceBishopBlack;

	// King
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceKingWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceKingBlack;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
