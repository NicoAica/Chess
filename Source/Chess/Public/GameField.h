// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	TArray<ATile*>& GetTitleArray();

	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;

	bool IsWinPosition(const FVector2D Position) const;

	inline bool IsValidPosition(const FVector2D Begin, const FVector2D End) const;

	TArray<int32> GetLine(const FVector2D Begin, const FVector2D End);
	
	bool AllEqual(const TArray<int32>& Array) const;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	TArray<ATile*> TileArray;

	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;

	static const int32 Not_Assigned = -1;

	// Propriety assigned in bluepri nt
	//UPROPERTY(BlueprintAssignable)
	//FOnReset OnResetEvent;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const int32 Size = 8;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//int32 WinSize;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	

	/* Material Instance Configuration */
	// Tile
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceTileGreen;
	UPROPERTY(EditAnywhere, Category="Material Instance Configuration")
	UMaterialInstance *MaterialInstanceTileWhite;

	// 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	

};
