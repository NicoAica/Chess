// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="Move HUD Settings")
	UTextBlock* ErrorMessageTextBox;

	UPROPERTY(EditAnywhere, Category="Move HUD Settings")
	TSubclassOf<UMoveListEntry> MoveListEntryClass;

	void AddInList(const FString& Move, bool const ButtonVisibility = false, const int32 MoveIndex = 0) const
	{
		if (MoveListEntryClass)
		{
			UMoveListEntry* MoveListEntry = CreateWidget<UMoveListEntry>(GetWorld(), MoveListEntryClass);
			MoveListEntry->MoveTextBlock->SetText(FText::FromString(Move));
			if (!ButtonVisibility)
			{
				MoveListEntry->ResetButton->SetVisibility(ESlateVisibility::Hidden);
			}
			MoveListEntry->MoveIndex = MoveIndex;
			MoveList->AddChild(MoveListEntry);
		}
	}

	void AddCheckInLastMove() const
	{
		if (MoveList->GetChildrenCount() > 0)
		{
			const UMoveListEntry* MoveListEntry = Cast<UMoveListEntry>(MoveList->GetChildAt(MoveList->GetChildrenCount() - 1));
			const FString Tmp = MoveListEntry->MoveTextBlock->GetText().ToString();
			MoveListEntry->MoveTextBlock->SetText(FText::FromString(Tmp + "+"));
		}
	}

	void AddCheckMateInLastMove() const
	{
		if (MoveList->GetChildrenCount() > 0)
		{
			const UMoveListEntry* MoveListEntry = Cast<UMoveListEntry>(MoveList->GetChildAt(MoveList->GetChildrenCount() - 1));
			const FString Tmp = MoveListEntry->MoveTextBlock->GetText().ToString();
			MoveListEntry->MoveTextBlock->SetText(FText::FromString(Tmp + "#"));
		}
	}

	void PopLastMove() const
	{
		if (MoveList->GetChildrenCount() > 0)
		{
			MoveList->RemoveChildAt(MoveList->GetChildrenCount() - 1);
		}
	}

	void SetErrorMessage(const FString& Message) const
	{
		ErrorMessageTextBox->SetVisibility(ESlateVisibility::Visible);
		ErrorMessageTextBox->SetText(FText::FromString(Message));
	}

	void HiddenErrorMessage() const
	{
		ErrorMessageTextBox->SetVisibility(ESlateVisibility::Hidden);
	}
	
};
