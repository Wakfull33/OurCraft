// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemComponent.h"
#include "GameFramework/Character.h"
#include "../Subsystems/DataAssetLoadingSubsystem.h"
#include "../UI/InventoryDataAsset.h"
#include "../UI/InventoryWidget.h"
#include "../UI/InventorySlotWidget.h"
#include "../UI/InventoryItemWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventorySystemComponent::UInventorySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerCharacter->InputComponent->BindAction("Inventory", IE_Pressed, this, &UInventorySystemComponent::ToggleInventory);

	DataAssetLoader = OwnerCharacter->GetGameInstance()->GetSubsystem<UDataAssetLoadingSubsystem>();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	InventoryDataAsset = DataAssetLoader->LoadDataAsset<UInventoryDataAsset>(AssetRegistryModule);

	if (InventoryDataAsset) {
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryDataAsset->InventoryWidgetReference);
		InventorySlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), InventoryDataAsset->InventorySlotWidgetReference);

		Inventory.SetNum(InventoryDataAsset->PlayerInventorySize);
	}
}


// Called every frame
void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//bool UInventorySystemComponent::AddItemStack(const FItemStack &ItemToAdd)
//{
//	//Check if inventory is full
//	if (Inventory.Num() < InventoryMaxSize) {
//		//Check if Item already exist
//		if (Inventory.Num() == 0) 
//		{
//			Inventory.Add(ItemToAdd);
//			return true;
//		}
//		else
//		{
//			for (int i = 0; i < Inventory.Num(); ++i) {
//				if (Inventory[i].ItemData == ItemToAdd.ItemData && Inventory[i].ItemCount < Inventory[i].ItemData.MaxStack) {
//					//Check if total count is less or equal to max item stack size
//					if (Inventory[i].ItemCount + ItemToAdd.ItemCount <= Inventory[i].ItemData.MaxStack)
//					{
//						UE_LOG(LogTemp, Warning, TEXT("Adding Item :    MaxStack:%d    Actual Stack:%d    After Stack:%d"), ItemToAdd.ItemData.MaxStack, Inventory[i].ItemCount, Inventory[i].ItemCount + ItemToAdd.ItemCount)
//						Inventory[i].ItemCount += ItemToAdd.ItemCount;
//					}
//					else
//					{
//						int Diff = (Inventory[i].ItemCount + ItemToAdd.ItemCount) - ItemToAdd.ItemData.MaxStack;
//
//						UE_LOG(LogTemp, Warning, TEXT("Adding Item (Need New Stack):    MaxStack:%d    Actual Stack:%d    New Stack:%d"), ItemToAdd.ItemData.MaxStack, Inventory[i].ItemCount, Diff)
//
//						Inventory[i].ItemCount = ItemToAdd.ItemData.MaxStack;
//						Inventory.Add(FItemStack(ItemToAdd.ItemData, Diff));
//					}
//					return true;
//				}
//			}
//			//Add Item
//			Inventory.Add(ItemToAdd);
//			return true;
//		}
//	}
//	else 
//	{
//		return false;
//	}
//}

bool UInventorySystemComponent::AddItemStack(FItemStack &ItemToAdd)
{
	for (int i = 0; i < InventoryDataAsset->PlayerInventorySize; ++i) {
		if (Inventory[i].ItemData == ItemToAdd.ItemData) {
			if (Inventory[i].ItemCount < Inventory[i].ItemData.MaxStack) {
				//Check if total count is less or equal to max item stack size
				if (Inventory[i].ItemCount + ItemToAdd.ItemCount <= Inventory[i].ItemData.MaxStack)
				{
					UE_LOG(LogTemp, Warning, TEXT("Adding Item :    MaxStack:%d    Actual Stack:%d    After Stack:%d"), ItemToAdd.ItemData.MaxStack, Inventory[i].ItemCount, Inventory[i].ItemCount + ItemToAdd.ItemCount)
					Inventory[i].ItemCount += ItemToAdd.ItemCount;

					return true;
				}
				else
				{
					int Diff = (Inventory[i].ItemCount + ItemToAdd.ItemCount) - ItemToAdd.ItemData.MaxStack;

					UE_LOG(LogTemp, Warning, TEXT("Adding Item (Need New Stack):    MaxStack:%d    Actual Stack:%d    New Stack:%d"), ItemToAdd.ItemData.MaxStack, Inventory[i].ItemCount, Diff)

						Inventory[i].ItemCount = ItemToAdd.ItemData.MaxStack;

					if (i < InventoryDataAsset->PlayerInventorySize - 1) {
						ItemToAdd.ItemCount -= Diff;
						return false;
					}

					Inventory.Add(FItemStack(ItemToAdd.ItemData, Diff));
					return true;
				}
			}
		}
		else if (Inventory[i].ItemData.Name == "Default Name") {
			Inventory[i] = ItemToAdd;
			return true;
		}
	}

	return false;
}

void UInventorySystemComponent::ToggleInventory()
{
	if (!IsInventoryOpen)
	{
		SetupInventorySlots();
		InventoryWidget->AddToViewport(100);
		IsInventoryOpen = true;
		PlayerController->SetInputMode(FInputModeGameAndUI::FInputModeGameAndUI());
		PlayerController->bShowMouseCursor = true;
		DebugInventoryToString();
	}
	else 
	{
		InventoryWidget->RemoveFromViewport();
		RemoveInventorySlots();
		IsInventoryOpen = false;
		PlayerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void UInventorySystemComponent::SetupInventorySlots()
{
	if (InventoryWidget && InventorySlotWidget) {
		for (int i = 0; i < Inventory.Num(); ++i)
		{
			UInventorySlotWidget* Slot = CreateWidget<UInventorySlotWidget>(GetWorld(), InventoryDataAsset->InventorySlotWidgetReference);
			Slot->InventorySystemComponent = this;
			Slot->SlotIndex = i;

			InventoryWidget->InventoryGrid->AddChildToGrid(Slot, i / 8, i % 8);

			if (Inventory[i].ItemData.Name != "Default Name")
			{
				UInventoryItemWidget* Item = CreateWidget<UInventoryItemWidget>(GetWorld(), InventoryDataAsset->InventoryItemWidgetReference);
				UpdateInventoryItemInfos(Item, i);

				UInventorySlotWidget* TempSlot = Cast<UInventorySlotWidget>(InventoryWidget->InventoryGrid->GetChildAt(i));
				TempSlot->SlotBorder->AddChild(Item);
			}
		}
	}
}

void UInventorySystemComponent::UpdateInventoryItemInfos(UInventorySlotWidget* Slot, int SlotIndex)
{
	UInventoryItemWidget* Item = Slot->GetSlotItem();

	if(Item == nullptr && Inventory[SlotIndex].ItemData.Name != "Default Name"){
		Item = CreateWidget<UInventoryItemWidget>(GetWorld(), InventoryDataAsset->InventoryItemWidgetReference);
		Slot->SlotBorder->AddChild(Item);
	}

	if (Inventory[SlotIndex].ItemData.Name != "Default Name" && Item) {
		Item->ItemIcon->SetBrushFromTexture(Inventory[SlotIndex].ItemData.Icon);
		Item->ItemIcon->SetBrushTintColor(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
		Item->ItemCount->SetVisibility(Inventory[SlotIndex].ItemCount <= 1 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		Item->ItemCount->SetColorAndOpacity(FSlateColor(Inventory[SlotIndex].ItemCount < Inventory[SlotIndex].ItemData.MaxStack ? FLinearColor(1.0f, 1.0f, 1.0f, 1.0f) : FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)));
		Item->ItemCount->SetText(FText::AsNumber(Inventory[SlotIndex].ItemCount));

		Item->ItemDataRef = Inventory[SlotIndex].ItemData;
	}
}

void UInventorySystemComponent::UpdateInventoryItemInfos(UInventoryItemWidget* Item, int SlotIndex)
{
	if (Inventory[SlotIndex].ItemData.Name != "Default Name") {
		Item->ItemIcon->SetBrushFromTexture(Inventory[SlotIndex].ItemData.Icon);
		Item->ItemIcon->SetBrushTintColor(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
		Item->ItemCount->SetVisibility(Inventory[SlotIndex].ItemCount <= 1 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		Item->ItemCount->SetColorAndOpacity(FSlateColor(Inventory[SlotIndex].ItemCount < Inventory[SlotIndex].ItemData.MaxStack ? FLinearColor(1.0f, 1.0f, 1.0f, 1.0f) : FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)));
		Item->ItemCount->SetText(FText::AsNumber(Inventory[SlotIndex].ItemCount));

		Item->ItemDataRef = Inventory[SlotIndex].ItemData;
	}
}

void UInventorySystemComponent::RemoveInventorySlots()
{
	if (InventoryWidget && InventorySlotWidget) {
		for (int i = Inventory.Num() - 1; i >= 0; --i)
		{
			InventoryWidget->InventoryGrid->RemoveChildAt(i);
		}
	}
}

void UInventorySystemComponent::SwapItemStacks(UInventorySlotWidget* InSlot, UInventorySlotWidget* OutSlot)
{
	if ((InSlot->SlotIndex >= 0 && InSlot->SlotIndex < Inventory.Num()) && (OutSlot->SlotIndex >= 0 && OutSlot->SlotIndex < Inventory.Num()))
	{
		if (Inventory[InSlot->SlotIndex].ItemData == Inventory[OutSlot->SlotIndex].ItemData) {
			FItemStack& InStack = Inventory[InSlot->SlotIndex];
			FItemStack& OutStack = Inventory[OutSlot->SlotIndex];

			if (OutStack.ItemCount + InStack.ItemCount <= OutStack.ItemData.MaxStack)
			{
				OutStack.ItemCount += InStack.ItemCount;
				InStack = FItemStack();
				InSlot->SlotBorder->RemoveChildAt(0);
			}
			else
			{
				int Diff = (InStack.ItemCount + OutStack.ItemCount) - OutStack.ItemData.MaxStack;
				OutStack.ItemCount = OutStack.ItemData.MaxStack;
				InStack.ItemCount = Diff;
				UpdateInventoryItemInfos(InSlot, InSlot->SlotIndex);
			}
			UpdateInventoryItemInfos(OutSlot, OutSlot->SlotIndex);
		}
		else {
			Inventory.Swap(InSlot->SlotIndex, OutSlot->SlotIndex);

			if (OutSlot->SlotBorder->GetChildrenCount() > 0) {
				UInventoryItemWidget* ItemToAdd = CreateWidget<UInventoryItemWidget>(GetWorld(), InventoryDataAsset->InventoryItemWidgetReference);
				UpdateInventoryItemInfos(ItemToAdd, InSlot->SlotIndex);

				InSlot->SlotBorder->RemoveChild(ItemToAdd);
				InSlot->SlotBorder->AddChild(OutSlot->SlotBorder->GetChildAt(0));
				OutSlot->SlotBorder->RemoveChildAt(0);
				OutSlot->SlotBorder->AddChild(ItemToAdd);
			}
			else {
				OutSlot->SlotBorder->AddChild(InSlot->SlotBorder->GetChildAt(0));
				InSlot->SlotBorder->RemoveChild(0);
			}
		}
	}
}

void UInventorySystemComponent::SplitItemStacks(UInventorySlotWidget* SlotToSplit, bool SplitInHalf)
{
	TPair<bool, UInventorySlotWidget*> InventoryFull = IsInventoryFull();
	if (InventoryFull.Key == false && Inventory[SlotToSplit->SlotIndex].ItemCount >= 2) {
		if (SplitInHalf) {
			int SplitedCount = (Inventory[SlotToSplit->SlotIndex].ItemCount / 2) + (Inventory[SlotToSplit->SlotIndex].ItemCount % 2);
			Inventory[SlotToSplit->SlotIndex].ItemCount /= 2;

			Inventory[InventoryFull.Value->SlotIndex] = FItemStack(Inventory[SlotToSplit->SlotIndex].ItemData, SplitedCount);

			UpdateInventoryItemInfos(SlotToSplit, SlotToSplit->SlotIndex);
			UpdateInventoryItemInfos(InventoryFull.Value, InventoryFull.Value->SlotIndex);
			if (InventoryFull.Value != nullptr) {
				UE_LOG(LogTemp, Warning, TEXT("Old Stack: [%d] -> %d	New Stack: [%d] -> %d"), SlotToSplit->SlotIndex, Inventory[SlotToSplit->SlotIndex].ItemCount, InventoryFull.Value->SlotIndex, Inventory[InventoryFull.Value->SlotIndex].ItemCount)
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Unable To Split Items: Inventory Is Full or not enought item to split in half"))
}

void UInventorySystemComponent::DebugInventoryToString()
{
	FString Return;

	for (int i = 0; i < Inventory.Num(); ++i) {
		if (Inventory[i].ItemData.Name != "Default Name")
			Return.Append("[O]");
		else
			Return.Append("[ ]");

		if (i < Inventory.Num() - 1)
			Return.Append(",");
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Return)
}

TPair<bool, UInventorySlotWidget*> UInventorySystemComponent::IsInventoryFull() {
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i].ItemData.Name == "Default Name") {
			UInventorySlotWidget* EmptySlot = Cast<UInventorySlotWidget>(InventoryWidget->InventoryGrid->GetChildAt(i));
			
			return TPairInitializer<bool, UInventorySlotWidget*>(false, EmptySlot);
		}
	}

	return TPairInitializer<bool, UInventorySlotWidget*>(true, nullptr);
}
