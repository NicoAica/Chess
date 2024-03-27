// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"

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
	
}

void AHumanPlayer::OnClick()
{

	UE_LOG(LogTemp, Error, TEXT("CIAO"));

	
	FHitResult Hit = FHitResult(ForceInit);

	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor( ECC_Pawn, true, Hit);

	if (Hit.bBlockingHit && IsMyTurn)
	{
		if (ATile* CurrTile = Cast<ATile>(Hit.GetActor()))
		{
			if (CurrTile->GetTileStatus() != ETileStatus::Empty)
			{
				// Check if pawn in tile is a pawn's player
				// Move Pawn
				IsMyTurn = false;
				
			}
		}
	}
}

