// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

#include "ChessGameInstance.h"
#include "ChessGameMode.h"
#include "Pieces/Pedestrian.h"
#include "Pieces/Piece.h"
#include "Pieces/Rook.h"

// Sets default values
AGameField::AGameField(): MaterialInstanceTileGreen(nullptr), MaterialInstanceTileWhite(nullptr),
                          MaterialInstancePedestrianWhite(nullptr),
                          MaterialInstancePedestrianBlack(nullptr),
                          MaterialInstanceQueenWhite(nullptr),
                          MaterialInstanceQueenBlack(nullptr),
                          MaterialInstanceKnightWhite(nullptr),
                          MaterialInstanceKnightBlack(nullptr),
                          MaterialInstanceRookWhite(nullptr),
                          MaterialInstanceRookBlack(nullptr),
                          MaterialInstanceBishopWhite(nullptr),
                          MaterialInstanceBishopBlack(nullptr),
                          MaterialInstanceKingWhite(nullptr),
                          MaterialInstanceKingBlack(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	TileSize = 120;
	TileScale = TileSize / 100;
}

void AGameField::UndoMoves(const int32 MoveNumber)
{
	if (Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->IsGameOver)
	{
		Cast<UChessGameInstance>(GetGameInstance())->SetErrorMessage("Game is over!");

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			Cast<UChessGameInstance>(GetGameInstance())->HiddenErrorMessage();
		}, 3.0f, false);
		return;
	}

	if (Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->CurrentPlayer != 0)
	{
		Cast<UChessGameInstance>(GetGameInstance())->SetErrorMessage("Wait your time to undo moves!");

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			Cast<UChessGameInstance>(GetGameInstance())->HiddenErrorMessage();
		}, 3.0f, false);
	}
	else
	{
		Cast<UChessGameInstance>(GetGameInstance())->UndoTillMove(MoveNumber);
	}
}

void AGameField::GenerateField()
{
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = GetRelativeLocationByXYPosition(x, y);
			ATile* Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location, FRotator::ZeroRotator);
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
			Obj->SetGridPosition(x, y);
			Obj->SetTileStatus(-1, Empty);

			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}

	SpawnPedestrianOnTiles();
	SpawnQueensOnTile();
	SpawnKnightsOnTile();
	SpawnRooksOnTile();
	SpawnBishopsOnTile();
	SpawnKingsOnTile();

	DefaultTileColor();
}

template <typename T>
void AGameField::SpawnPiece(TSubclassOf<T> Class, const int32 X, const int32 Y, const int32 Player, UMaterialInstance* MaterialInstance, bool const IsKingTile)
{
	FVector Location = GetRelativeLocationByXYPosition(X, Y);
	Location.Z = 4.5;

	ATile* Obj = *TileMap.Find(FVector2D(X, Y));
	APiece* Piece = GetWorld()->SpawnActor<APiece>(Class, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Piece->StaticMeshComponent->SetMaterial(0, MaterialInstance);
	Piece->SetActualTile(Obj);
	Piece->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(Player, Occupied);
	Obj->SetPiece(Piece);
	Obj->B_IsKingTile = IsKingTile;
	
}

void AGameField::SpawnPedestrianOnTiles()
{
	
	for (int i = 0; i < Size; i++)
	{
		// White Pedestrian
		SpawnPiece(PedestrianClass, 1, i, 0, MaterialInstancePedestrianWhite); 

		// Black Pedestrian
		SpawnPiece(PedestrianClass, 6, i, 1, MaterialInstancePedestrianBlack);
	}
}

void AGameField::SpawnQueensOnTile()
{
	// White Queen
	SpawnPiece(QueenClass, 0, 3, 0, MaterialInstanceQueenWhite);
	
	// Black Queen
	SpawnPiece(QueenClass, 7, 3, 1, MaterialInstanceQueenBlack);
}

void AGameField::SpawnKnightsOnTile()
{
	// White Knights
	SpawnPiece(KnightClass, 0, 1, 0, MaterialInstanceKnightWhite);
	SpawnPiece(KnightClass, 0, 6, 0, MaterialInstanceKnightWhite);
	
	// Black Knights
	SpawnPiece(KnightClass, 7, 1, 1, MaterialInstanceKnightBlack);
	SpawnPiece(KnightClass, 7, 6, 1, MaterialInstanceKnightBlack);
}

void AGameField::SpawnRooksOnTile()
{
	// White Rooks
	SpawnPiece(RookClass, 0, 0, 0, MaterialInstanceRookWhite);
	SpawnPiece(RookClass, 0, 7, 0, MaterialInstanceRookWhite);
	
	// Black Rooks
	SpawnPiece(RookClass, 7, 0, 1, MaterialInstanceRookBlack);
	SpawnPiece(RookClass, 7, 7, 1, MaterialInstanceRookBlack);
}

void AGameField::SpawnBishopsOnTile()
{
	// White Bishops
	SpawnPiece(BishopClass, 0, 2, 0, MaterialInstanceBishopWhite);
	SpawnPiece(BishopClass, 0, 5, 0, MaterialInstanceBishopWhite);

	// Black Bishops
	SpawnPiece(BishopClass, 7, 2, 1, MaterialInstanceBishopBlack);
	SpawnPiece(BishopClass, 7, 5, 1, MaterialInstanceBishopBlack);
}

void AGameField::SpawnKingsOnTile()
{
	// White King
	SpawnPiece(KingClass, 0, 4, 0, MaterialInstanceKingWhite, true);

	// Black King
	SpawnPiece(KingClass, 7, 4, 1, MaterialInstanceKingBlack, true);
}

void AGameField::DefaultTileColor()
{
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			if ((x + y) % 2 == 0)
			{
				ATile** Tile = TileMap.Find(FVector2D(x, y));
				(*Tile)->StaticMeshComponent->SetMaterial(0, MaterialInstanceTileGreen);
			}
			else
			{
				ATile** Tile = TileMap.Find(FVector2D(x, y));
				(*Tile)->StaticMeshComponent->SetMaterial(0, MaterialInstanceTileWhite);
			}
		}
	}
}

FVector2D AGameField::GetPosition(const FHitResult& Hit)
{
	return Cast<ATile>(Hit.GetActor())->GetGridPosition();
}

TArray<ATile*>& AGameField::GetTileArray()
{
	return TileArray;
}

TMap<FVector2D, ATile*>& AGameField::GetTileMap()
{
	return TileMap;
}

TMap<FVector2D, ATile*>& AGameField::GetYourTile(const int32 Player, TMap<FVector2D, ATile*>& Tmp)
{
	auto It = TileMap.CreateIterator();
	while (It)
	{
		if (It.Value()->GetOwner() == Player)
		{
			Tmp.Add(It.Key(), It.Value());
		}
		++It;
	}
	return Tmp;
}

bool AGameField::IsCheck(const int32 Player)
{
	TMap<FVector2D, ATile*> Tmp;
	GetYourTile(Player, Tmp);
	
	auto It = Tmp.CreateIterator();
	while (It)
	{
		It.Value()->GetPiece()->CalculatePossibleMove(false);
		auto It2 = It.Value()->GetPiece()->PossibleMove.CreateIterator();
		while (It2)
		{
			if (It2.Value()->B_IsKingTile)
			{
				return true;
			}
			++It2;
		}
		++It;
	}
	return false;
}

bool AGameField::IsCheckMate(const int32 Player)
{
	return IsStaleMate(Player);
}

bool AGameField::IsStaleMate(const int32 Player)
{
	TMap<FVector2D, ATile*> Tmp;
	GetYourTile(Player, Tmp);

	auto It = Tmp.CreateIterator();

	int32 Count = 0;

	while (It)
	{
		It.Value()->GetPiece()->CalculatePossibleMove(true);
		if (It.Value()->GetPiece()->PossibleMove.Num())
		{
			Count++;
		}
		++It;
	}
	return Count == 0;
}




int32 AGameField::ValueOfChessBoard()
{
	// Get White Pieces
	TMap<FVector2D, ATile*> WhitePieces;
	GetYourTile(0, WhitePieces);

	// Get Black Pieces
	TMap<FVector2D, ATile*> BlackPieces;
	GetYourTile(1, BlackPieces);

	int32 Value = 0;

	auto It = WhitePieces.CreateIterator();
	while (It)
	{
		Value += ValueOfPiece(It.Value()->GetPiece());
		++It;
	}
	auto It1 = BlackPieces.CreateIterator();
	while (It1)
	{
		Value -= ValueOfPiece(It1.Value()->GetPiece());
		++It1;
	}

	return Value;
}

int32 AGameField::ValueOfPiece(const APiece* Piece)
{
	if (Cast<APedestrian>(Piece))
	{
		return 1;
	}
	if (Cast<ABishop>(Piece) || Cast<AKnight>(Piece))
	{
		return 3;
	}
	if (Cast<ARook>(Piece))
	{
		return 5;
	}
	if (Cast<AQueen>(Piece))
	{
		return 9;
	}

	// King doesn't have value
	return 0;
}


FVector AGameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX, InY, 0);
}

FVector2D AGameField::GetXYPositionByRelativeLocation(const FVector& Location)
{
	const double x = Location[0];
	const double y = Location[1];
	return FVector2D(x, y);
}


// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
}

void AGameField::Promote(ATile* FuturePosition, int32 const Player)
{
	FVector Location = GetRelativeLocationByXYPosition(FuturePosition->GetGridPosition().X,FuturePosition->GetGridPosition().Y);
	Location.Z = 4.5;

	APiece* NewPiece = GetWorld()->SpawnActor<APiece>(QueenClass, Location,
												   FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	NewPiece->SetActualTile(FuturePosition);
	if (Player)
	{
		NewPiece->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenBlack);
	}
	else
	{
		NewPiece->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenWhite);
	}

	NewPiece->SetActorScale3D(FVector(TileScale, TileScale, 1));
	FuturePosition->SetTileStatus(Player, Occupied, false);
	FuturePosition->SetPiece(NewPiece);
	NewPiece->CalculatePossibleMove();
}

void AGameField::PromotePiece(const int32 Piece)
{

	TmpSelectedPiece->SelfDestroy();

	FVector Location = GetRelativeLocationByXYPosition(TmpFutureTile->GetGridPosition().X,TmpFutureTile->GetGridPosition().Y);
	Location.Z = 4.5;
	
	UMaterialInstance* MaterialInstance = nullptr;
	TSubclassOf<APiece> PieceClass = nullptr;
	
	switch (Piece)
	{
	case 0:
		PieceClass = BishopClass;
		MaterialInstance = TmpPlayer == 0 ? MaterialInstanceBishopWhite : MaterialInstanceBishopBlack;
		break;
	case 1:
		PieceClass = KnightClass;
		MaterialInstance = TmpPlayer == 0 ? MaterialInstanceKnightWhite : MaterialInstanceKnightBlack;
		break;
	case 2:
		PieceClass = RookClass;
		MaterialInstance = TmpPlayer == 0 ? MaterialInstanceRookWhite : MaterialInstanceRookBlack;
		break;
	case 3:
		PieceClass = QueenClass;
		MaterialInstance = TmpPlayer == 0 ? MaterialInstanceQueenWhite : MaterialInstanceQueenBlack;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Piece"));
	}

	APiece* NewPiece = GetWorld()->SpawnActor<APiece>(PieceClass, Location,FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	NewPiece->StaticMeshComponent->SetMaterial(0, MaterialInstance);
	
								
	NewPiece->SetActualTile(TmpFutureTile);
	
	NewPiece->SetActorScale3D(FVector(TileScale, TileScale, 1));
	TmpFutureTile->SetTileStatus(TmpPlayer, Occupied, false);
	TmpFutureTile->SetPiece(NewPiece);
	NewPiece->CalculatePossibleMove();
	
	TmpSelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
	TmpSelectedPiece->GetActualTile()->SetPiece(nullptr);

	TmpMove->SetPromotedPiece(TmpFutureTile->GetPiece());
	Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->TurnNextPlayer(TmpMove);
}

// Called every frame
void AGameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGameField::MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool const Eat, const int32 Player, UMove* Move)
{
	if (Eat)
	{
		FutureTile->GetPiece()->SelfDestroy();
	}

	if (FutureTile->GetGridPosition().X == (Player == 1 ? 0 : 7) && Cast<APedestrian>(SelectedPiece))
	{
		if (Player == 0)
		{

			TmpSelectedPiece = SelectedPiece;
			TmpFutureTile = FutureTile;
			TmpPlayer = Player;
			TmpMove = Move;
			
			UUserWidget* ChoosePromotionPieceHUD = CreateWidget<UUserWidget>(GetWorld(), ChoosePromotionPieceClass);
			ChoosePromotionPieceHUD->AddToViewport();
			
			return true;
		}
		
		SelectedPiece->SelfDestroy();
		Promote(FutureTile, Player);
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		return false;
		
	}
	
		// Calc future location
		const FVector2D FutureTilePosition = FutureTile->GetGridPosition();
		FVector const FuturePosition = FVector(FutureTilePosition.X * 120, FutureTilePosition.Y * 120, SelectedPiece->GetActorLocation().Z);
	
		// Move Actor
		SelectedPiece->SetActorLocation(FuturePosition);

		// Change Tile Info
		FutureTile->SetTileStatus(Player, Occupied, SelectedPiece->GetActualTile()->B_IsKingTile);
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		SelectedPiece->SetActualTile(FutureTile);
		FutureTile->SetPiece(SelectedPiece);
	

	return false;
}
