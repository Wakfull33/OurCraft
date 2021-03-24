// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySplitterWidget.generated.h"

#pragma region Forward Declarations

class USlider;
class UButton;
class UTextBlock;

class UInventorySlotWidget;

struct FItemStack;

#pragma endregion

/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventorySplitterWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* SplittingSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* OutStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonConfirm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonCancel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	UInventorySlotWidget* InSlot = nullptr;

	virtual void NativeConstruct();

	FItemStack ItemStack;

	UFUNCTION(BlueprintCallable)
	void SliderValueChanged(float value);

	UFUNCTION(BlueprintCallable)
	void ConfirmSplitting();

	UFUNCTION(BlueprintCallable)
	void AbortSplitting();
};
