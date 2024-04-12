// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pieces/Pedestrian.h"
#include "Tile/Tile.h"
#include "GameFramework/Actor.h" 
#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Supports/Move.h"
#include "GameField.generated.h"

UCLASS()
class CHESS_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();
	
	// This method is called from HUD to undo the moves
	UFUNCTION(BlueprintCallable)
	void UndoMoves(int32 MoveNumber);

	// Uso this method to span tiles and pieces
	void GenerateField();

	// Use this method to get position of the hit
	static FVector2D GetPosition(const FHitResult& Hit);

	// Return the tile array
	TArray<ATile*>& GetTileArray();

	// Return the tile map
	TMap<FVector2D, ATile*>& GetTileMap();

	// Return only the tiles that belong to the player
	TMap<FVector2D, ATile*>& GetYourTile(const int32 Player, TMap<FVector2D, ATile*>& Tmp);

	// Return if the player make check
	bool IsCheck(const int32 Player);

	// Check if Player make a check
	bool IsCheckMate(const int32 Player);

	// Check if there are available moves
	bool IsStaleMate(const int32 Player);

	// Promote
	void Promote(ATile* FuturePosition, int32 Player);

	// Use this method to calculate the value of the chess board
	int32 ValueOfChessBoard();

	// Use this method to calculate the value of the piece
	int32 ValueOfPiece(const APiece* Piece);
	
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	static FVector2D GetXYPositionByRelativeLocation(const FVector& Location);

	// Use this method to color the tile spawned to default
	void DefaultTileColor();

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

	// Map of the tiles
	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;
	
	UPROPERTY(Transient)
	TArray<ATile*> TileArray;

	const int32 Size = 8;
	
	float TileSize;
	float TileScale;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ChoosePromotionPieceClass;

	/* Temp Variables for Promotion */
	UPROPERTY()
	APiece* TmpSelectedPiece;
	UPROPERTY()
	ATile* TmpFutureTile;
	UPROPERTY()
	int32 TmpPlayer;
	UPROPERTY()
	UMove* TmpMove;

	// This func is called from hud to promote the piece
	UFUNCTION(BlueprintCallable)
	void PromotePiece(const int32 Piece);

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

	template <typename T>
	void SpawnPiece(TSubclassOf<T> Class, const int32 X, const int32 Y, const int32 Player, UMaterialInstance* MaterialInstance, bool const IsKingTile = false);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Use this method to move the actor to the future tile (return true if it is a promotion)
	bool MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool Eat, const int32 Player, UMove* Move = nullptr);
};


