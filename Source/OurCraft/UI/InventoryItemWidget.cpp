// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"
#include "InventoryTooltipWidget.h"
#include "../DataAssetLoadingSubsystem.h"
#include "InventoryDataAsset.h"

void UInventoryItemWidget::NativeConstruct()
{
	//UDataAssetLoadingSubsystem* DataAssetLoader = GetGameInstance()->GetSubsystem<UDataAssetLoadingSubsystem>();
	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//UInventoryDataAsset* InventoryDataAsset = InventoryDataAsset = DataAssetLoader->LoadDataAsset<UInventoryDataAsset>(AssetRegistryModule);

	//if (InventoryDataAsset) {
	//	Tooltip = CreateWidget<UInventoryTooltipWidget>(GetWorld(), InventoryDataAsset->InventoryTooltipWidgetReference);
	//	UE_LOG(LogTemp, Warning, TEXT("%s    %s"), *InventoryDataAsset->InventoryTooltipWidgetReference->GetName())
	//}
}

void UInventoryItemWidget::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//if (!IsTooltipVisible) {

	//	UDataAssetLoadingSubsystem* DataAssetLoader = GetGameInstance()->GetSubsystem<UDataAssetLoadingSubsystem>();
	//	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//	UInventoryDataAsset* InventoryDataAsset = InventoryDataAsset = DataAssetLoader->LoadDataAsset<UInventoryDataAsset>(AssetRegistryModule);

	//	if (InventoryDataAsset) {
	//		Tooltip = CreateWidget<UInventoryTooltipWidget>(GetWorld(), InventoryDataAsset->InventoryTooltipWidgetReference);
	//		
	//		if (Tooltip) {
	//			Tooltip->AddToViewport(200);
	//			IsTooltipVisible = true;
	//		}
	//	}
	//}
}

FReply UInventoryItemWidget::NativeOnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//if (IsTooltipVisible) {
	//	//Tooltip->SetPositionInViewport(MouseEvent.GetScreenSpacePosition());
	//	Tooltip->SetPositionInViewport(MouseEvent.Pos);
	//}

	return FReply::Handled();
}

void UInventoryItemWidget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	//if (IsTooltipVisible) {
	//	Tooltip->RemoveFromViewport();
	//	Tooltip = nullptr;
	//	IsTooltipVisible = false;
	//}
}

void UInventoryItemWidget::SetupTooltipInfos()
{
	if (Tooltip) {
		Tooltip->ItemName->SetText(FText::FromString(ItemDataRef.Name));
		Tooltip->ItemDescription->SetText(FText::FromString(ItemDataRef.Description));
		//Tooltip->ItemStats->SetText(FText::FromString(ItemData.Stats));
		Tooltip->ItemValue->SetText(FText::FromString(FString::FormatAsNumber(ItemDataRef.Value)));
		UE_LOG(LogTemp, Warning, TEXT("Tooltip Setup"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tooltip is Null"))
	}
}
