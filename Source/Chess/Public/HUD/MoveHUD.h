// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
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

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="Move HUD Settings")
	UTextBlock* ErrorMessageTextBox;

	UPROPERTY(EditAnywhere, Category="Move HUD Settings")
	TSubclassOf<UMoveListEntry> MoveListEntryClass;

	// Add MoveListEntry to the MoveList
	void AddInList(const FString& Move, bool const ButtonVisibility = false, const int32 MoveIndex = 0) const;

	// Add + to the last MoveListEntry
	void AddCheckInLastMove() const;

	// Add # to the last MoveListEntry
	void AddCheckMateInLastMove() const;

	// Pop last move in stack
	void PopLastMove() const;

	// Set the error message
	void SetErrorMessage(const FString& Message) const;

	// Hide the error message
	void HiddenErrorMessage() const;
	
};
