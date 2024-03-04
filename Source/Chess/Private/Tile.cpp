// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Chess/Public/Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);


	// TODO: Non è detto che sia vuota
	Status = Empty;
	PlayerOwner =- 1;
	TileGridPosition = FVector2D(0, 0);
	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

inline void ATile::SetTitleStatus(const int32 TileOwner, const ETileStatus TileStatus)
{
	PlayerOwner = TileOwner;
	Status = TileStatus;
}

inline ETileStatus ATile::GetTileStatus()
{
	return Status;
}

inline int32 ATile::GetOwner()
{
	return PlayerOwner;
}

inline void ATile::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

inline FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

// Called every frame
/*
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
