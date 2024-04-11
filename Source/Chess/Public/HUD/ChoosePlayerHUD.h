// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ChoosePlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChoosePlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget), Category="Choose Player Settings")
	UButton* MinMaxButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget), Category="Choose Player Settings")
	UButton* RandomButton;
};
