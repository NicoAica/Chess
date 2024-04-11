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
}

// Called when the game starts or when spawned
void AHumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

	auto GMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

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
				
				CurrPiece->CalculatePossibleMove();
				
				CurrPiece->ColorTilePossibleMove();
			}
			else 
			{
				if (SelectedPiece != nullptr)
				{
					ATile* FutureTile = CurrPiece->GetActualTile();
					if (FVector2D const CurrentPosition = FutureTile->GetGridPosition(); SelectedPiece->CanGoTo(CurrentPosition))
					{
						IsMyTurn = false;
						UMove* Move = NewObject<UMove>();
						Move->Initialize(SelectedPiece->GetActualTile(), FutureTile, SelectedPiece, true, CurrPiece);
						
						if (!GMode->GField->MoveActorTo(FutureTile, SelectedPiece, true, 0, Move))
						{
							Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer(Move);
						}
						
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
					
					IsMyTurn = false;
					UMove* Move = NewObject<UMove>();
					Move->Initialize(SelectedPiece->GetActualTile(), CurrTile, SelectedPiece, false);
						
					if (!GMode->GField->MoveActorTo(CurrTile, SelectedPiece, false, 0, Move))
					{
						Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer(Move);
					}
					
				}
			}
		}
	}
}

