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

	ATile* Tile = nullptr;
	TMap<FVector2D, ATile*> BlackTileMap;
	GField->GetYourTile(1, BlackTileMap);
	
	bool B_HasAvailableMove = false;

	do
	{
		auto It = BlackTileMap.CreateConstIterator();
		const int32 Rand = rand() % BlackTileMap.Num();
		int32 i = 0;

		while (It && i < Rand)
		{
			++It;
			++i;
		}
		
		if (It.Value()->GetPiece()->CalculatePossibleMove(true))
		{
			B_HasAvailableMove = true;
			Tile = It.Value();
		}
		else
		{
			BlackTileMap.Remove(It.Key());
		}
	} while (!B_HasAvailableMove);
	
	Tile->GetPiece()->ColorTilePossibleMove();
	Tile->SelectedTileSetColor();

	ATile* FutureTile = Tile->GetPiece()->GetRandomAvailableTile();

	FTimerHandle UnusedHandle;
	
	GetWorldTimerManager().SetTimer(UnusedHandle, [this, FutureTile, Tile, GMode]()
	{
		UMove *Move = NewObject<UMove>();
		Move->Initialize(Tile, FutureTile, Tile->GetPiece(), FutureTile->GetPiece() != nullptr, FutureTile->GetPiece());;

		bool const B_IsPromotionMove = FutureTile->GetGridPosition().X == 0 && Cast<APedestrian>(Tile->GetPiece());	
		
		GMode->GField->MoveActorTo(FutureTile, Tile->GetPiece(), FutureTile->GetOwner() == 0, 1);
		
		if (B_IsPromotionMove)
		{
			Move->SetPromotedPiece(FutureTile->GetPiece());
		}
		
		GMode->TurnNextPlayer(Move);
	}, 0.5f, false);
}

/*
void ARandomPlayer::MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool const Eat) const
{
	if (Eat)
	{
		FutureTile->GetPiece()->SelfDestroy();
	}

	if (FutureTile->GetGridPosition().X == 0 && Cast<APedestrian>(SelectedPiece))
	{
		SelectedPiece->SelfDestroy();
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->Promote(FutureTile, 1);
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
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
	
}
*/