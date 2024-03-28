 // Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

#include "ChessGameMode.h"
#include "Pieces/Pedestrian.h"
#include "Piece.h"

 // Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileSize = 120;
	
}

 void AGameField::ResetField()
 {
	for (ATile* Obj : TileArray)
	{
		Obj->SetTileStatus(Not_Assigned, Empty);
	}

	 OnResetEvent.Broadcast();

	AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->IsGameOver = false;
	GameMode->MoveCounter = 0;
	// respawn all pawns
	GameMode->ChoosePlayerAndStartGame();
	
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
	SpawnQueensOnTile();
	SpawnKnightsOnTile();
	DefaultTileColor();
 }

void AGameField::SpawnPedestrianOnTiles()
{
	const float TileScale = TileSize / 100;
	for (int i = 0; i < Size; i++)
	{
		// White Pedestrian
		FVector Location = GetRelativeLocationByXYPosition(1, i);
		Location.Z = 4.5;
		ATile* Obj = *TileMap.Find(FVector2D(1, i));
		APedestrian* Pedestrian = GetWorld()->SpawnActor<APedestrian>(PedestrianClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
		Pedestrian->SetActualTile(Obj);
		Pedestrian->StaticMeshComponent->SetMaterial(0, MaterialInstancePedestrianWhite);
		Pedestrian->SetActorScale3D(FVector(TileScale, TileScale, 1));
		Obj->SetTileStatus(0, Occupied);
		Obj->SetPiece(Pedestrian);

		// Black Pedestrian
		Location = GetRelativeLocationByXYPosition(6, i);
		Location.Z = 4.5;
		Obj = *TileMap.Find(FVector2D(6, i));
		Pedestrian = GetWorld()->SpawnActor<APedestrian>(PedestrianClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
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
	ATile* Obj = *TileMap.Find(FVector2D(0, 3));
	AQueen* Queen = GetWorld()->SpawnActor<AQueen>(QueenClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Queen->SetActualTile(Obj);
	Queen->StaticMeshComponent->SetMaterial(0, MaterialInstanceQueenWhite);
	Queen->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Queen);

	// Black Queen
	Location = GetRelativeLocationByXYPosition(7, 3);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 3));
	Queen = GetWorld()->SpawnActor<AQueen>(QueenClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
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
	AKnight* Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightWhite);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Knight);
	Location = GetRelativeLocationByXYPosition(0, 6);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(0, 6));
	Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightWhite);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(0, Occupied);
	Obj->SetPiece(Knight);

	// Black Knights
	Location = GetRelativeLocationByXYPosition(7, 1);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 1));
	Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightBlack);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Knight);
	Location = GetRelativeLocationByXYPosition(7, 6);
	Location.Z = 4.5;
	Obj = *TileMap.Find(FVector2D(7, 6));
	Knight = GetWorld()->SpawnActor<AKnight>(KnightClass, Location, FRotationMatrix::MakeFromX(FVector(0, 1, 0)).Rotator());
	Knight->SetActualTile(Obj);
	Knight->StaticMeshComponent->SetMaterial(0, MaterialInstanceKnightBlack);
	Knight->SetActorScale3D(FVector(TileScale, TileScale, 1));
	Obj->SetTileStatus(1, Occupied);
	Obj->SetPiece(Knight);
	
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

 FVector AGameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
 {
	return TileSize * FVector(InX, InY, 0);
 }

 FVector2D AGameField::GetXYPositionByRelativeLocation(const FVector& Location) const
 {
	const double x = Location[0];
	const double y = Location[1];
	return  FVector2D(x, y);
 }

 bool AGameField::IsWinPosition(const FVector2D Position) const
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
	for (ATile* Tile :TileArray)
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
	for (ATile* Tile :TileArray)
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

