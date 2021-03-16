// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssetLoadingSubsystem.h"
#include "UI/InteractionDataAsset.h"
#include "UI/InventoryDataAsset.h"

void UDataAssetLoadingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	InventoryDataAsset = LoadDataAsset<UInventoryDataAsset>(AssetRegistryModule);
	InteractionDataAsset = LoadDataAsset<UInteractionDataAsset>(AssetRegistryModule);
}

void UDataAssetLoadingSubsystem::Deinitialize()
{

}
