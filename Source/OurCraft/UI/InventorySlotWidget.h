// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "../Characters/InventorySystemComponent.h"
#include "InventorySlotWidget.generated.h"

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
	class UInventoryItemWidget* GetSlotItem();
};
