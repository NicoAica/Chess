// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"

#include "ChessGameMode.h"

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PlayerOwner = nullptr;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	//AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

	// Da fare nella game field
	// GameMode->GField->OnResetEvent.AddDynamic(this, &APiece::SelfDestroy);
	
}

void APiece::SetPlayerOwner(IPlayerInterface *Player)
{
	PlayerOwner = Player;
}

void APiece::SelfDestroy()
{
	Destroy();
}

void APiece::SetActualTile(ATile* Tile)
{
	ActualTile = Tile;
}

ATile* APiece::GetActualTile() const
{
	return ActualTile;
}

void APiece::ColorTilePossibleMove()
{
	auto It = PossibleMove.CreateIterator();
	while (It)
	{
		It->Value->PossibleMoveColor();
		++It;
	}
}

bool APiece::CanGoTo(FVector2D const Position)
{
	if (PossibleMove.Find(Position))
	{
		return true;
	}
	return false;
}

ATile* APiece::GetRandomAvailableTile()
{
	auto It = PossibleMove.CreateIterator();
	if (!PossibleMove.Num()) return nullptr;
	int32 const Rand = rand() % PossibleMove.Num();
	for (int32 i = 0; i < Rand; i++)
		++It;
	return It->Value;
}

