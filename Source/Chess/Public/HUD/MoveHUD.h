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

	void AddInList(const FString& Move, bool const ButtonVisibility = false, const int32 MoveIndex = 0) const;

	void AddCheckInLastMove() const;

	void AddCheckMateInLastMove() const;

	void PopLastMove() const;

	void SetErrorMessage(const FString& Message) const;

	void HiddenErrorMessage() const;
	
};
