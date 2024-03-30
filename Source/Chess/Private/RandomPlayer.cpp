// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPlayer.h"

#include "ChessGameMode.h"

// Sets default values
ARandomPlayer::ARandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARandomPlayer::OnTurn()
{
	auto const GMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
	auto const GField = GMode->GField;

	ATile* Tile;
	
	do
	{
		Tile = GField->GetTileOfBlackPiece(rand() % GField->GetNumberOfBlackPiece());
	}
	while (!Tile->GetPiece()->CalculatePossibleMove());
	
	Tile->GetPiece()->ColorTilePossibleMove();
	Tile->SelectedTileSetColor();

	ATile* FutureTile = Tile->GetPiece()->GetRandomAvailableTile();

	FTimerHandle UnusedHandle;
	
	GetWorldTimerManager().SetTimer(UnusedHandle, [this, FutureTile, Tile, GMode]()
	{
		MoveActorTo(FutureTile, Tile->GetPiece(), FutureTile->GetOwner() == 0);
		GMode->TurnNextPlayer();
	}, 2.0f, false);


	//MoveActorTo(FutureTile, Tile->Piece, FutureTile->GetTileStatus() != Empty);
	
}

void ARandomPlayer::MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool const Eat) const
{
	// Calc future location
	const FVector2D FutureTilePosition = FutureTile->GetGridPosition();
	FVector const FuturePosition = FVector(FutureTilePosition.X * 120, FutureTilePosition.Y * 120, SelectedPiece->GetActorLocation().Z);

	// Move Actor
	SelectedPiece->SetActorLocation(FuturePosition);

	// Change Tile Info
	FutureTile->SetTileStatus(1, Occupied, SelectedPiece->GetActualTile()->B_IsKingTile);
	SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
	SelectedPiece->GetActualTile()->SetPiece(nullptr);
	SelectedPiece->SetActualTile(FutureTile);

	if (Eat)
	{
		FutureTile->GetPiece()->SelfDestroy();
	}

	FutureTile->SetPiece(SelectedPiece);

	// Remove possible move color
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->DefaultTileColor();
	
}



