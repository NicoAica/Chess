// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/RandomPlayer.h"

#include "ChessGameMode.h"

// Sets default values
ARandomPlayer::ARandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARandomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ARandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARandomPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI Turn"));
	auto const GMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
	auto const GField = GMode->GField;

	ATile* Tile;
	int32 Test = 0;
	
	do
	{
		Test++;
		Tile = GField->GetTileOfBlackPiece(rand() % GField->GetNumberOfBlackPiece());
		if (Test > 150)
		{
			// TODO implement patta
			return;
		}
	}
	while (!Tile->GetPiece()->CalculatePossibleMove());
	
	Tile->GetPiece()->ColorTilePossibleMove();
	Tile->SelectedTileSetColor();

	ATile* FutureTile = Tile->GetPiece()->GetRandomAvailableTile();

	FTimerHandle UnusedHandle;
	
	GetWorldTimerManager().SetTimer(UnusedHandle, [this, FutureTile, Tile, GMode]()
	{
		MoveActorTo(FutureTile, Tile->GetPiece(), FutureTile->GetOwner() == 0);
		UE_LOG(LogTemp, Error, TEXT("Valore della scacchiera: %d"), GMode->GField->ValueOfChessBoard());
		GMode->TurnNextPlayer();
	}, 0.1f, false);
}

void ARandomPlayer::MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool const Eat) const
{

	if (Eat)
	{
		FutureTile->GetPiece()->SelfDestroy();
	}
	
	/* Promote */
	if (FutureTile->GetGridPosition().X == 0 && Cast<APedestrian>(SelectedPiece))
	{
		UE_LOG(LogTemp, Error, TEXT("Promozione"));
		
		// Remove reference
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		
		// Spawn queen
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->Promote(FutureTile, 1);

		SelectedPiece->SelfDestroy();
		
	}
	else
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
		FutureTile->SetPiece(SelectedPiece);
	}
	
	// Remove possible move color
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->DefaultTileColor();
	
}



