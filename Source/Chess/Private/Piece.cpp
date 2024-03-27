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
	AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

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

