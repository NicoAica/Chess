// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/HumanPlayer.h"

#include "ChessGameMode.h"
#include "Tile.h"

// Sets default values
AHumanPlayer::AHumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set first player 
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Set camera as root component
	SetRootComponent(Camera);

	PlayerNumber = -1;
	
}

// Called when the game starts or when spawned
void AHumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHumanPlayer::MoveActorTo(ATile* FutureTile)
{

	/* Promote */
	if (FutureTile->GetGridPosition().X == 7 && Cast<APedestrian>(SelectedPiece))
	{
		
		// Remove reference
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		
		// Spawn queen
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->Promote(FutureTile, 0);

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
		FutureTile->SetTileStatus(0, Occupied, SelectedPiece->GetActualTile()->B_IsKingTile);
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		SelectedPiece->SetActualTile(FutureTile);
		FutureTile->SetPiece(SelectedPiece);
	}

	// Remove possible move color
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->DefaultTileColor();
	
	// Initialize variable for next time
	SelectedPiece = nullptr;
	IsMyTurn = false;
	
}

void AHumanPlayer::MoveActorTo(APiece* EvilPiece)
{
	ATile* Tmp = EvilPiece->GetActualTile();
	MoveActorTo(Tmp);
	EvilPiece->SelfDestroy();
}

// Called every frame
void AHumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHumanPlayer::OnTurn()
{ 
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
}

void AHumanPlayer::OnClick()
{
	FHitResult Hit = FHitResult(ForceInit);

	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Pawn, true, Hit);

	if (Hit.bBlockingHit && IsMyTurn)
	{
		
		if (APiece* CurrPiece = Cast<APiece>(Hit.GetActor()))
		{
			// Check if click is on owner piece
			if (CurrPiece->GetActualTile()->GetOwner() == 0)
			{
				SelectedPiece = CurrPiece;
				
				Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->DefaultTileColor();
				CurrPiece->GetActualTile()->SelectedTileSetColor();
				
				int32 Test = CurrPiece->CalculatePossibleMove();
				
				CurrPiece->ColorTilePossibleMove();
			}
			else 
			{
				if (SelectedPiece != nullptr)
				{
					ATile* FutureTile = CurrPiece->GetActualTile();
					if (FVector2D const CurrentPosition = FutureTile->GetGridPosition(); SelectedPiece->CanGoTo(CurrentPosition))
					{
						FMove* Move = new FMove(SelectedPiece->GetActualTile(), FutureTile, SelectedPiece, false);
						MoveActorTo(CurrPiece);
						Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer(Move);
					}
				}
			}
		}
		else if (ATile* CurrTile = Cast<ATile>(Hit.GetActor()))
		{
			if (SelectedPiece != nullptr)
			{
				if (FVector2D const CurrentPosition = CurrTile->GetGridPosition(); SelectedPiece->CanGoTo(CurrentPosition))
				{
					MoveActorTo(CurrTile);
					FMove* Move = new FMove(SelectedPiece->GetActualTile(), CurrTile, SelectedPiece, false);
					Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer(Move);
				}
			}
		}
	}
}

