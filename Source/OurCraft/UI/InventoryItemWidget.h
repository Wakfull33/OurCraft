// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Utils/StructUtils.h"
#include "../Characters/InventorySystemComponent.h"
#include "InventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, ExposeOnSpawn = true))
	UTextBlock* ItemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, ExposeOnSpawn = true))
	UImage* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryTooltipWidget* Tooltip = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsTooltipVisible = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FItemData ItemDataRef;

private:


public:
	virtual void NativeConstruct();

	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	virtual FReply NativeOnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent);

	UFUNCTION(BlueprintCallable)
	void SetupTooltipInfos();


};
