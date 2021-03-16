// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Player.h"
#include "../Characters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryDataAsset.h"
#include "AssetRegistryModule.h"

void AHUD_Player::BeginPlay()
{
	Super::BeginPlay();

	//AMainCharacter* Main = Cast<AMainCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	UInventoryDataAsset* InventoryDataAsset = nullptr;
	TArray<FAssetData> AssetsDatas = TArray<FAssetData>();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(FName(*(UInventoryDataAsset::StaticClass()->GetName())), AssetsDatas);
	if (AssetsDatas.Num() > 0)
		InventoryDataAsset = Cast<UInventoryDataAsset>(AssetsDatas[0].GetAsset());

	//if (InventoryDataAsset)
	//	InteractibleListWidgetReference = InventoryDataAsset->InteractibleListWidgetReference;

	//UInteractibleListWidget* NewWidget = CreateWidget<UInteractibleListWidget>(GetWorld(), InteractibleListWidgetReference);

	//if (NewWidget) {
	//	InteractibleList = NewWidget;
	//	NewWidget->AddToViewport();
	//}
}