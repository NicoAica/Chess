 // Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"
 
 // Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileSize = 120;
	
}

 void AGameField::ResetField()
 {
 }

 void AGameField::GenerateField()
 {
	
	// Load Material instances
/*
	const FString MaterialInstanceGreenTilePath = TEXT("/Game/Materials/MI_GreenTile.MI_GreenTile"); 
	UMaterialInstance* MaterialInstanceGreen = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, *MaterialInstanceGreenTilePath));

	const FString MaterialInstanceWhiteTilePath = TEXT("/Game/Materials/MI_WhiteTile.MI_WhiteTile"); 
	UMaterialInstance* MaterialInstanceWhite = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, *MaterialInstanceWhiteTilePath));
*/	
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{ 
			FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
			ATile* Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location, FRotator::ZeroRotator);
			const float TileScale = TileSize / 100;
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
			Obj->SetGridPosition(x, y);

			// Color the tile
			if ((x + y) % 2 == 0)
			{
				Obj->StaticMeshComponent->SetMaterial(0, MaterialInstanceTileGreen);
			}
			else
			{
				Obj->StaticMeshComponent->SetMaterial(0, MaterialInstanceTileWhite);

			}
			
			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}
 }


 FVector2D AGameField::GetPosition(const FHitResult& Hit)
 {
	return Cast<ATile>(Hit.GetActor())->GetGridPosition(); 
 }

 TArray<ATile*>& AGameField::GetTitleArray()
 {
	return TileArray;
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

// Called every frame
void AGameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

