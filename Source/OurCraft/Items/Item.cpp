// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "AssetRegistryModule.h"
#include "../UI/InteractionDataAsset.h"
#include "../Characters/InventorySystemComponent.h"
#include "../Characters/InteractionSystemComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnConstruction(const FTransform& Transform)
{
	if(!DataTable.IsNull())
	{
		FItemData Data = *DataTable.GetRow<FItemData>("");
		StaticMeshComponent->SetStaticMesh(Data.StaticMesh);
		ItemStack = { Data, 1 };
	}
}

void AItem::Interact_Implementation(AActor* Other)
{
	bool IsPickedUp = false;

	for (UActorComponent* Component : Other->GetComponents())
	{
		if (Component && Component->GetClass() == UInventorySystemComponent::StaticClass())
		{
			IsPickedUp = Cast<UInventorySystemComponent>(Component)->AddItemStack(ItemStack);
		}
		if (IsPickedUp) {
			if (Component && Component->GetClass() == UInteractionSystemComponent::StaticClass())
			{
				Cast<UInteractionSystemComponent>(Component)->RemoveObject(this);
			}
			Destroy();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%s Interact With %s"), *Other->GetName(), *GetName())
}

FInteractionDetails AItem::GetInteractionDetails_Implementation() 
{
	FInteractionDetails InteractionDetails;

	InteractionDetails.InteractionIcon = ItemStack.ItemData.Icon;
	InteractionDetails.InteractionName = ItemStack.ItemData.Name;

	return InteractionDetails;
}