// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

#pragma region Forward Declarations

class UInventorySystemComponent;
class UBorder;
class UInventoryItemWidget;

#pragma endregion


/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	UInventorySystemComponent* InventorySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UBorder* SlotBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	int SlotIndex;

	UFUNCTION(BlueprintCallable)
	UInventoryItemWidget* GetSlotItem();
};
