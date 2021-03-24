// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryDataAsset.generated.h"

#pragma region Forward Declarations

class UInteractibleSlotWidget;

class UInventoryWidget;
class UInventorySlotWidget;
class UInventoryItemWidget;
class UInventoryTooltipWidget;
class UInventorySplitterWidget;

#pragma endregion

/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<UInteractibleSlotWidget> InteractibleSlotWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<UInventoryWidget> InventoryWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<UInventorySlotWidget> InventorySlotWidgetReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<UInventoryItemWidget> InventoryItemWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf< UInventoryTooltipWidget> InventoryTooltipWidgetReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Widgets")
	class TSubclassOf<UInventorySplitterWidget> InventorySplitterWidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int PlayerInventorySize;

};
