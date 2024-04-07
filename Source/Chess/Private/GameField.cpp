// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

#include "ChessGameInstance.h"
#include "ChessGameMode.h"
#include "Pieces/Pedestrian.h"
#include "Piece.h"
#include "Pieces/Rook.h"

// Sets default values
AGameField::AGameField()
{
	PrimaryActorTick.bCanEverTick = false;

	TileSize = 120;
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


	// Reset possible move (With undo we can't use the same possible move)
	/*for (ATile* Tile : TileArray)
	{
		if (Tile->GetPiece())
		{
			Tile->GetPiece()->CalculatePossibleMove();
		}
	}*/
}

void AGameField::GenerateField()
{
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = GetRelativeLocationByXYPosition(x, y);
			ATile* Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location, FRotator::ZeroRotator);
			const float TileScale = TileSize / 100;
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
			Obj->SetGridPosition(x, y);
			Obj->SetTileStatus(-1, Empty);

			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}
	SpawnPedestrianOnTiles();
	//SpawnQueensOnTile();
	//SpawnKnightsOnTile();
	//SpawnRooksOnTile();
	//SpawnBishopsOnTile();
	SpawnKingsOnTile();

	DefaultTileColor();
}

void AGameField::SpawnPedestrianOnTiles()
{
	const float TileScale = TileSize / 100;
	/*
		FVector Location = GetRelativeLocationByXYPosition(2, 0);
		Location.Z = 4.5;
		ATile* Obj = *TileMap.Find(FVector2D(2, 0));
		ARook* Pedestrian = GetWorld()->SpawnActor<ARook>(RookClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
		Pedestrian->SetActualTile(Obj);
		Pedestrian->StaticMeshComponent->SetMaterial(0, MaterialInstanceRookWhite);
		Pedestrian->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Obj->SetTileStatus(0, Occupied);
		Obj->SetPiece(Pedestrian);
	
		Location = GetRelativeLocationByXYPosition(1, 0);
		Location.Z = 4.5;
		Obj = *TileMap.Find(FVector2D(1, 0));
		AKnight* Pedestria = GetWorld()->SpawnActor<AKnight>(KnightClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
		Pedestria->SetActualTile(Obj);
		Pedestria->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightWhite);
		Pedestria->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Obj->SetTileStatus(0, Occupied);
		Obj->SetPiece(Pedestria);
	
		Location = GetRelativeLocationByXYPosition(1, 2);
		Location.Z = 4.5;
		Obj = *TileMap.Find(FVector2D(1, 2));
		ABishop* Pedestri = GetWorld()->SpawnActor<ABishop>(BishopClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
		Pedestri->SetActualTile(Obj);
		Pedestri->StaticMeshComponent->SetMaterial(0, MaterialInstanceBishopWhite);
		Pedestri->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Obj->SetTileStatus(0, Occupied);
		Obj->SetPiece(Pedestri);
	
		Location = GetRelativeLocationByXYPosition(0, 1);
		Location.Z = 4.5;
		Obj = *TileMap.Find(FVector2D(0, 1));
		Pedestri = GetWorld()->SpawnActor<ABishop>(BishopClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
		Pedestri->SetActualTile(Obj);
		Pedestri->StaticMeshComponent->SetMaterial(0, MaterialInstanceBishopBlack);
		Pedestri->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Obj->SetTileStatus(1, Occupied);
		Obj->SetPiece(Pedestri);
	
		
		*/
	for (int i = 0; i < Size; i++)
	{
		// White Pedestrian
		FVector Location = GetRelativeLocationByXYPosition(1, i);
		Location.Z = 4.5;
		ATile* Obj = *TileMap.Find(FVector2D(1, i));
		APedestrian* Pedestrian = GetWorld()->SpawnActor<APedestrian>(PedestrianClass, Location,
		                                                              FRotationMatrix::MakeFromX(FVector(0, 1, 0)).
		                                                              Rotator());
		Pedestrian->SetActualTile(Obj);
		Pedestrian->StaticMeshComponent->SetMaterial(0, MaterialInstancePedestrianWhite);
		Pedestrian->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Obj->SetTileStatus(0, Occupied);
		Obj->SetPiece(Pedestrian);

		// Black Pedestrian
		Location = GetRelativeLocationByXYPosition(3, i);
		Location.Z = 4.5;
		Obj = *TileMap.Find(FVector2D(3, i));
		Pedestrian = GetWorld()->SpawnActor<APedestrian>(PedestrianClass, Location,
		                                                 FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
		Pedestrian->StaticMeshComponent->SetMaterial(0, MaterialInstancePedestrianBlack);
		Pedestrian->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Pedestrian->SetActualTile(Obj);
		Obj->SetTileStatus(1, Occupied);
		Obj->SetPiece(Pedestrian);
	}
}

void AGameField::SpawnQueensOnTile()
{
	const float TileScale = TileSize / 100;

	// White Queen
	FVector Location = GetRelativeLocationByXYPosition(0, 3);
	Location.Z = 4.5;
	/*ATile* Obj = *TileMap.Find(FVector2D(0, 3));
	AQueen* Queen = GetWorld()->SpawnActor<AQueen>(QueenClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Queen->SetActualTile(Obj);
	Queen->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenWhite);
	Queen->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Queen);
*/
	// Black Queen
	Location = GetRelativeLocationByXYPosition(7, 3);
	Location.Z = 4.5;
	ATile* Obj = *TileMap.Find(FVector2D(7, 3));
	AQueen* Queen = GetWorld()->SpawnActor<AQueen>(QueenClass, Location,
	                                               FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Queen->SetActualTile(Obj);
	Queen->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenBlack);
	Queen->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Queen);
}

void AGameField::SpawnKnightsOnTile()
{
	const float TileScale = TileSize / 100;

	// White Knights
	FVector Location = GetRelativeLocationByXYPosition(0, 1);
	Location.Z = 4.5;
	ATile* Obj = *TileMap.Find(FVector2D(0, 1));
	AKnight* Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location,
	                                                  FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightWhite);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Knight);
	Location = GetRelativeLocationByXYPosition(0, 6);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(0, 6));
	Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location,
	                                         FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightWhite);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Knight);

	// Black Knights
	Location = GetRelativeLocationByXYPosition(7, 1);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 1));
	Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location,
	                                         FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightBlack);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Knight);
	Location = GetRelativeLocationByXYPosition(7, 6);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 6));
	Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location,
	                                         FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightBlack);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Knight);
}

void AGameField::SpawnRooksOnTile()
{
	const float TileScale = TileSize / 100;

	// White Rooks
	FVector Location = GetRelativeLocationByXYPosition(0, 0);
	Location.Z = 4.5;
	ATile* Obj = *TileMap.Find(FVector2D(0, 0));
	ARook* Rook = GetWorld()->SpawnActor<ARook>(RookClass, Location,
	                                            FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Rook->SetActualTile(Obj);
	Rook->StaticMeshComponent->SetMaterial(0, MaterialInstanceRookWhite);
	Rook->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Rook);
	Location = GetRelativeLocationByXYPosition(0, 7);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(0, 7));
	Rook = GetWorld()->SpawnActor<ARook>(RookClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Rook->SetActualTile(Obj);
	Rook->StaticMeshComponent->SetMaterial(0, MaterialInstanceRookWhite);
	Rook->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Rook);

	// Black Rooks
	Location = GetRelativeLocationByXYPosition(7, 0);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 0));
	Rook = GetWorld()->SpawnActor<ARook>(RookClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Rook->SetActualTile(Obj);
	Rook->StaticMeshComponent->SetMaterial(0, MaterialInstanceRookBlack);
	Rook->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Rook);
	Location = GetRelativeLocationByXYPosition(7, 7);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 7));
	Rook = GetWorld()->SpawnActor<ARook>(RookClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Rook->SetActualTile(Obj);
	Rook->StaticMeshComponent->SetMaterial(0, MaterialInstanceRookBlack);
	Rook->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Rook);
}

void AGameField::SpawnBishopsOnTile()
{
	const float TileScale = TileSize / 100;

	// White Bishops
	FVector Location = GetRelativeLocationByXYPosition(0, 2);
	Location.Z = 4.5;
	ATile* Obj = *TileMap.Find(FVector2D(0, 2));
	ABishop* Bishop = GetWorld()->SpawnActor<ABishop>(BishopClass, Location,
	                                                  FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Bishop->SetActualTile(Obj);
	Bishop->StaticMeshComponent->SetMaterial(0, MaterialInstanceBishopWhite);
	Bishop->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Bishop);
	Location = GetRelativeLocationByXYPosition(0, 5);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(0, 5));
	Bishop = GetWorld()->SpawnActor<ABishop>(BishopClass, Location,
	                                         FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Bishop->SetActualTile(Obj);
	Bishop->StaticMeshComponent->SetMaterial(0, MaterialInstanceBishopWhite);
	Bishop->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Bishop);

	// Black Bishops
	Location = GetRelativeLocationByXYPosition(7, 2);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 2));
	Bishop = GetWorld()->SpawnActor<ABishop>(BishopClass, Location,
	                                         FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Bishop->SetActualTile(Obj);
	Bishop->StaticMeshComponent->SetMaterial(0, MaterialInstanceBishopBlack);
	Bishop->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Bishop);
	Location = GetRelativeLocationByXYPosition(7, 5);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 5));
	Bishop = GetWorld()->SpawnActor<ABishop>(BishopClass, Location,
	                                         FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Bishop->SetActualTile(Obj);
	Bishop->StaticMeshComponent->SetMaterial(0, MaterialInstanceBishopBlack);
	Bishop->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Bishop);
}

void AGameField::SpawnKingsOnTile()
{
	const float TileScale = TileSize / 100;

	// White King
	FVector Location = GetRelativeLocationByXYPosition(0, 4);
	Location.Z = 4.5;
	ATile* Obj = *TileMap.Find(FVector2D(0, 4));
	AKing* King = GetWorld()->SpawnActor<AKing>(KingClass, Location,
	                                            FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	King->SetActualTile(Obj);
	King->StaticMeshComponent->SetMaterial(0, MaterialInstanceKingWhite);
	King->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied, true);
	Obj->SetPiece(King);
	Obj->B_IsKingTile = true;


	// Black King
	Location = GetRelativeLocationByXYPosition(7, 4);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 4));
	King = GetWorld()->SpawnActor<AKing>(KingClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	King->SetActualTile(Obj);
	King->StaticMeshComponent->SetMaterial(0, MaterialInstanceKingBlack);
	King->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied, true);
	Obj->SetPiece(King);
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

	//UE_LOG(LogTemp, Error, TEXT("Player %d ha %d pedine"), Player, Tmp.Num());

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
	// Controllo se per ogni pedina del player non ci sono mosse possibili
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


void AGameField::Promote(ATile* FuturePosition, int32 const Player)
{
	const float TileScale = TileSize / 100;

	FVector Location = GetRelativeLocationByXYPosition(FuturePosition->GetGridPosition().X,FuturePosition->GetGridPosition().Y);
	Location.Z = 4.5;

	AQueen* Queen = GetWorld()->SpawnActor<AQueen>(QueenClass, Location,
	                                               FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Queen->SetActualTile(FuturePosition);
	if (Player)
	{
		Queen->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenBlack);
	}
	else
	{
		Queen->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenWhite);
	}

	Queen->SetActorScale3D(FVector(TileScale, TileScale, 1));
	FuturePosition->SetTileStatus(Player, Occupied, false);
	FuturePosition->SetPiece(Queen);
	Queen->CalculatePossibleMove();
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

bool AGameField::IsWinPosition(const FVector2D Position)
{
	return false; // TODO
}

bool AGameField::IsValidPosition(const FVector2D Begin, const FVector2D End) const
{
	return false; // TODO
}

TArray<int32> AGameField::GetLine(const FVector2D Begin, const FVector2D End)
{
	return TArray<int32>();
}

bool AGameField::AllEqual(const TArray<int32>& Array) const
{
	return false; // TODO
}

// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
}

int32 AGameField::GetNumberOfBlackPiece()
{
	int32 Count = 0;
	for (ATile* Tile : TileArray)
	{
		if (Tile->GetOwner() == 1)
		{
			Count++;
		}
	}
	return Count;
}

ATile* AGameField::GetTileOfBlackPiece(const int32 N)
{
	int32 Count = 0;
	ATile* Tmp = nullptr;
	for (ATile* Tile : TileArray)
	{
		if (Tile->GetOwner() == 1)
		{
			Tmp = Tile;
			Count++;
			if (Count > N)
			{
				return Tmp;
			}
		}
	}
	return Tmp;
}

// Called every frame
void AGameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameField::MoveActorTo(ATile* FutureTile, APiece* SelectedPiece, bool const Eat, const int32 Player) const
{
	if (Eat)
	{
		FutureTile->GetPiece()->SelfDestroy();
	}

	if (FutureTile->GetGridPosition().X == (Player == 1 ? 0 : 7) && Cast<APedestrian>(SelectedPiece))
	{
		SelectedPiece->SelfDestroy();
		Cast<AChessGameMode>(GetWorld()->GetAuthGameMode())->GField->Promote(FutureTile, Player);
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
		FutureTile->SetTileStatus(Player, Occupied, SelectedPiece->GetActualTile()->B_IsKingTile);
		SelectedPiece->GetActualTile()->SetTileStatus(-1, Empty);
		SelectedPiece->GetActualTile()->SetPiece(nullptr);
		SelectedPiece->SetActualTile(FutureTile);
		FutureTile->SetPiece(SelectedPiece);
	}
	
}