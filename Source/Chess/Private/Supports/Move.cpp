// Fill out your copyright notice in the Description page of Project Settings.


#include "Supports/Move.h"

#include "Piece.h"

UMove::UMove()
{
	Origin = nullptr;
	Destination = nullptr;
	Piece = nullptr;
	Eat = false;
	EatenPiece = nullptr;
	PromotedPiece = nullptr;
}

UMove::UMove(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece, APiece* InPromotedPiece)
{
	this->Origin = InOrigin;
	this->Destination = InDestination;
	this->Piece = InPiece;
	this->Eat = InEat;
	this->EatenPiece = InEatenPiece;
	this->PromotedPiece = InPromotedPiece;
}

void UMove::Initialize(ATile* InOrigin, ATile* InDestination, APiece* InPiece, bool InEat, APiece* InEatenPiece, APiece* InPromotedPiece)
{
	this->Origin = InOrigin;
	this->Destination = InDestination;
	this->Piece = InPiece;
	this->Eat = InEat;
	this->EatenPiece = InEatenPiece;
	this->PromotedPiece = InPromotedPiece;
}

void UMove::SetPromotedPiece(APiece* InPromotedPiece)
{
	this->PromotedPiece = this->Piece;
	this->Piece = InPromotedPiece;
}

void UMove::SetPieceFromPromotedPiece()
{
	Piece->SelfDestroy(); // Hard Destroy
	Piece = PromotedPiece;
	
}
