// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySplitterWidget.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "InventorySlotWidget.h"
#include "../Utils/StructUtils.h"
#include "../Characters/InventorySystemComponent.h"

void UInventorySplitterWidget::NativeConstruct()
{
	ItemStack = InSlot->InventorySystemComponent->Inventory[InSlot->SlotIndex];

	SplittingSlider->SetValue(0.5);
	InStackCount->SetText(FText::FromString(FString::FormatAsNumber(ItemStack.ItemCount * SplittingSlider->GetValue())));
	OutStackCount->SetText(FText::FromString(FString::FormatAsNumber(ItemStack.ItemCount * SplittingSlider->GetValue() + ItemStack.ItemCount % 2)));

	//SplittingSlider->ValueDelegate.BindUFunction(this, FName("SliderValueChanged"));
}

void UInventorySplitterWidget::SliderValueChanged(float value)
{
	int InCount = ItemStack.ItemCount * SplittingSlider->GetValue();
	int OutCount = ItemStack.ItemCount * (1 - value) + ItemStack.ItemCount % 2;

	InCount = FMath::Clamp(InCount, 1, ItemStack.ItemCount - 1);
	OutCount = FMath::Clamp(OutCount, 1, ItemStack.ItemCount - 1);

	InStackCount->SetText(FText::FromString(FString::FormatAsNumber(InCount)));
	OutStackCount->SetText(FText::FromString(FString::FormatAsNumber(OutCount)));
	UE_LOG(LogTemp, Warning, TEXT("Value has changed: %f"), value)
}

void UInventorySplitterWidget::ConfirmSplitting() 
{
	int InCount = ItemStack.ItemCount * SplittingSlider->GetValue();
	InCount = FMath::Clamp(InCount, 1, ItemStack.ItemCount - 1);

	InSlot->InventorySystemComponent->SplitItemStacks(InSlot, InCount);
	RemoveFromViewport();
}

void UInventorySplitterWidget::AbortSplitting() 
{
	RemoveFromViewport();
}
