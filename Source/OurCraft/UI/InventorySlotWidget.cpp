// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "InventoryItemWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "../Characters/InventorySystemComponent.h"

UInventoryItemWidget* UInventorySlotWidget::GetSlotItem()
{
	if(SlotBorder->GetChildrenCount() > 0)
		return Cast<UInventoryItemWidget>(SlotBorder->GetChildAt(0));
	else
		return nullptr;
}
