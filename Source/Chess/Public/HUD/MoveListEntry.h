// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveListEntry.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMoveListEntry : public UUserWidget
{
	GENERATED_BODY()

	
	
public:

	UPROPERTY(EditAnywhere, meta=(BindWidget), Category="Move List Entry Settings")
	class UTextBlock* MoveTextBlock;

	
};
