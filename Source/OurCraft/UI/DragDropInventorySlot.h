// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.h"
#include "DragDropInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API UDragDropInventorySlot : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	int ItemIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	UInventorySlotWidget* InSlot;

};
