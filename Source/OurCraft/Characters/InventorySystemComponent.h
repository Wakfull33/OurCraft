// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "../Utils/StructUtils.h"
#include "Components/ActorComponent.h"
#include "InventorySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURCRAFT_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemStack> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InventoryMaxSize;

	UPROPERTY()
	bool IsInventoryOpen = false;

	UPROPERTY()
	class ACharacter* OwnerCharacter = nullptr;

	UPROPERTY()
	class APlayerController* PlayerController = nullptr;

	UPROPERTY()
	class UInventoryDataAsset* InventoryDataAsset = nullptr;

	UPROPERTY()
	class UDataAssetLoadingSubsystem* DataAssetLoader = nullptr;

	UPROPERTY()
	class UInventorySlotWidget* InventorySlotWidget = nullptr;

	UPROPERTY()
	class UInventoryItemWidget* InventoryItemWidget = nullptr;

	UPROPERTY()
	class UInventoryWidget* InventoryWidget = nullptr;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool AddItemStack(FItemStack &ItemToAdd);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	UFUNCTION(BlueprintCallable)
	void SetupInventorySlots();

	UFUNCTION(BlueprintCallable)
	void UpdateInventoryItemInfos(UInventorySlotWidget* Slot, int SlotIndex);
	
	void UpdateInventoryItemInfos(UInventoryItemWidget* Item, int SlotIndex);

	UFUNCTION(BlueprintCallable)
	void RemoveInventorySlots();

	UFUNCTION(BlueprintCallable)
	void SwapItemStacks(UInventorySlotWidget* InSlot, UInventorySlotWidget* OutSlot);

	UFUNCTION(BlueprintCallable)
	void SplitItemStacks(UInventorySlotWidget* SlotToSplit, bool SplitInHalf);

	UFUNCTION()
	void DebugInventoryToString();

	TPair<bool, UInventorySlotWidget*> IsInventoryFull();
};
