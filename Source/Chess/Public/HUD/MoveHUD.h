// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "MoveHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMoveHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, meta=(BindWidget), Category="Move HUD Settings")
	UScrollBox* MoveList;

	UPROPERTY(EditAnywhere, Category="Move HUD Settings")
	TSubclassOf<UMoveListEntry> MoveListEntryClass;

	void Test(const FString& Move) const
	{
		if (MoveListEntryClass)
		{
			UMoveListEntry* MoveListEntry = CreateWidget<UMoveListEntry>(GetWorld(), MoveListEntryClass);
			MoveListEntry->MoveTextBlock->SetText(FText::FromString(Move));
			MoveList->AddChild(MoveListEntry);
		}
	}

	
};
