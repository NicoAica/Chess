// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticleHelper.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum ETileStatus : uint8
{
	Empty UMETA(DisplayName = "Empty"),
	Occupied UMETA(DisplayName = "Occupied")
};

UCLASS()
class CHESS_API ATile : public AActor
{
	GENERATED_BODY() 
	
public:	
	// Sets default values for this actor's properties
	ATile();

	void SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus);
	
	ETileStatus GetTileStatus();
	int32 GetOwner();
	
	void SetGridPosition(const double InX, const double InY);
	FVector2D GetGridPosition();

	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETileStatus> Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D TileGridPosition;
	
//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
