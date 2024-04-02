// Fill out your copyright notice in the Description page of Project Settings.


#include "Supports/Move.h"

FMove::FMove()
{
	Origin = nullptr;
	Destination = nullptr;
	Piece = nullptr;
	Eat = false;
}

FMove::FMove(ATile* Origin, ATile* Destination, APiece* Piece, bool Eat)
{
	this->Origin = Origin;
	this->Destination = Destination;
	this->Piece = Piece;
	this->Eat = Eat;
}

FMove::~FMove()
{
}
