// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<class UInteractibleSlotWidget> InteractibleSlotWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<class UInventoryWidget> InventoryWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<class UInventorySlotWidget> InventorySlotWidgetReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<class UInventoryItemWidget> InventoryItemWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<class UInventoryTooltipWidget> InventoryTooltipWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int PlayerInventorySize;

};
