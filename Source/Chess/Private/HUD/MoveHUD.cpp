// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MoveListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "HUD/MoveHUD.h"

void UMoveHUD::AddInList(const FString& Move, bool const ButtonVisibility, const int32 MoveIndex) const
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

void UMoveHUD::AddCheckInLastMove() const
{
	if (MoveList->GetChildrenCount() > 0)
	{
		const UMoveListEntry* MoveListEntry = Cast<UMoveListEntry>(MoveList->GetChildAt(MoveList->GetChildrenCount() - 1));
		const FString Tmp = MoveListEntry->MoveTextBlock->GetText().ToString();
		MoveListEntry->MoveTextBlock->SetText(FText::FromString(Tmp + "+"));
	}
}

void UMoveHUD::AddCheckMateInLastMove() const
{
	if (MoveList->GetChildrenCount() > 0)
	{
		const UMoveListEntry* MoveListEntry = Cast<UMoveListEntry>(MoveList->GetChildAt(MoveList->GetChildrenCount() - 1));
		const FString Tmp = MoveListEntry->MoveTextBlock->GetText().ToString();
		MoveListEntry->MoveTextBlock->SetText(FText::FromString(Tmp + "#"));
	}
}

void UMoveHUD::PopLastMove() const
{
	if (MoveList->GetChildrenCount() > 0)
	{
		MoveList->RemoveChildAt(MoveList->GetChildrenCount() - 1);
	}
}

void UMoveHUD::SetErrorMessage(const FString& Message) const
{
	ErrorMessageTextBox->SetVisibility(ESlateVisibility::Visible);
	ErrorMessageTextBox->SetText(FText::FromString(Message));
}

void UMoveHUD::HiddenErrorMessage() const
{
	ErrorMessageTextBox->SetVisibility(ESlateVisibility::Hidden);
}
