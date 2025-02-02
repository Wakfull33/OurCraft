// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

#pragma region Forward Declarations

class UTextBlock;
class UButton;
class UGridPanel;

#pragma endregion

/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* InventoryName = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ButtonClose = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* InventoryGrid = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* InventoryToolbar = nullptr;

private:
	//virtual bool Initialize() override;
};
