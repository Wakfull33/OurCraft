// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistryModule.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataAssetLoadingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API UDataAssetLoadingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInventoryDataAsset* InventoryDataAsset = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInteractionDataAsset* InteractionDataAsset = nullptr;

	template<typename TDataAsset>
	TDataAsset* LoadDataAsset(const FAssetRegistryModule& AssetRegistryModule) 
	{
		TArray<FAssetData> DataAssets = TArray<FAssetData>();

		AssetRegistryModule.Get().GetAssetsByClass(FName(*(TDataAsset::StaticClass()->GetName())), DataAssets);

		if (DataAssets.Num() > 0) {
			return Cast<TDataAsset>(DataAssets[0].GetAsset());
		}
		else
		{
			return nullptr;
		}
	};
};
