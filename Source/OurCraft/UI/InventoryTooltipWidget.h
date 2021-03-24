// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltipWidget.generated.h"

#pragma region Forward Declarations

class UTextBlock;

#pragma endregion


/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventoryTooltipWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* ItemName = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* ItemDescription = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* ItemStats = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* ItemValue = nullptr;

};
