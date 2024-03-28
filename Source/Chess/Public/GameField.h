// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pedestrian.h"
#include "Tile.h"
#include "GameFramework/Actor.h" 
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

	FVector2D GetPosition(const FHitResult& Hit);

	TArray<ATile*>& GetTileArray();

	TMap<FVector2D, ATile*>& GetTileMap();

	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;

	bool IsWinPosition(const FVector2D Position) const;

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APedestrian> PedestrianClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	

	/* Material Instance Configuration */
	// Tile
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceTileGreen;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceTileWhite;

	// Piece
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstancePedestrianWhite;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstancePedestrianBlack;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	

};
