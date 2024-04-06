// Fill out your copyright notice in the Description page of Project Settings.


#include "Supports/Move.h"

UMove::UMove()
{
	Origin = nullptr;
	Destination = nullptr;
	Piece = nullptr;
	Eat = false;
	EatenPiece = nullptr;
}

UMove::UMove(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece)
{
	this->Origin = InOrigin;
	this->Destination = InDestination;
	this->Piece = InPiece;
	this->Eat = InEat;
	this->EatenPiece = InEatenPiece;
}

void UMove::Initialize(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece)
{
	this->Origin = InOrigin;
	this->Destination = InDestination;
	this->Piece = InPiece;
	this->Eat = InEat;
	this->EatenPiece = InEatenPiece;
}
