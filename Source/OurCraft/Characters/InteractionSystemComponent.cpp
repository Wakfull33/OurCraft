// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystemComponent.h"
#include "../UI/InventoryDataAsset.h"
#include "../UI/InteractionDataAsset.h"
#include "../UI/InteractibleSlotWidget.h"
#include "../Subsystems/DataAssetLoadingSubsystem.h"
#include "../UI/HUD_Player.h"
#include "../Utils/InteractionInterface.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "AssetRegistryModule.h"
#include "Styling/SlateColor.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInteractionSystemComponent::UInteractionSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...

}


// Called when the game starts
void UInteractionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("HUD: %s"), *PlayerController->GetHUD()->GetName())
			Hud = Cast<AHUD_Player>(PlayerController->GetHUD());
		if (Hud)
			//WidgetList = Hud->InteractibleList;
			UE_LOG(LogTemp, Warning, TEXT("HUD found"))
		else
			UE_LOG(LogTemp, Warning, TEXT("Unable to cast HUD"))
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerCharacter->InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractionSystemComponent::Interact);

	DataAssetLoader = OwnerCharacter->GetGameInstance()->GetSubsystem<UDataAssetLoadingSubsystem>();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	InventoryDataAsset = DataAssetLoader->LoadDataAsset<UInventoryDataAsset>(AssetRegistryModule);
	InteractionDataAsset = DataAssetLoader->LoadDataAsset<UInteractionDataAsset>(AssetRegistryModule);

	if (InventoryDataAsset) {
		InteractibleSlotWidget = CreateWidget<UInteractibleSlotWidget>(GetWorld(), InventoryDataAsset->InteractibleSlotWidgetReference);
	}
}


// Called every frame
void UInteractionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/* Add Object-Widget pair to the Map when interactible object is overlapped*/
bool UInteractionSystemComponent::AddObject(AActor* Object)
{
	if (!InteractibleActors.Contains(Object) && InteractibleSlotWidget)
	{
		SetupSlotInfo(InteractibleSlotWidget, Object);
		//PlayerController->SetInputMode(InteractionInputMode);

		if (InteractibleActors.Num() == 0)
		{
			InteractibleActors.Add(Object);
			//UE_LOG(LogTemp, Warning, TEXT("Adding Actor: %s"), *Object->GetName())

			if (!IsSlotWidgetDisplayed) 
			{
				InteractibleSlotWidget->AddToViewport();
				SetupSlotInfo(InteractibleSlotWidget, Object);
				IsSlotWidgetDisplayed = true;
			}
		}
		else if (InteractibleActors.Num() > 0) 
		{
			InteractibleActors.Add(Object);
		}

		return true;
	}
	else {
		return false;
	}
}

/* Remove Object-Widget pair to the Map when interactible object stop overlapping or is remove*/
bool UInteractionSystemComponent::RemoveObject(AActor* Object) {
	if (InteractibleActors.Contains(Object)) 
	{
		//Remove Widget in the map
		InteractibleActors.Remove(Object);
		//UE_LOG(LogTemp, Warning, TEXT("Removing Actor: %s"), *Object->GetName())


		//If map is empty remove WidgetList from the viewport
		if (InteractibleActors.Num() != 0)
		{
			SetupSlotInfo(InteractibleSlotWidget, InteractibleActors[0]);
		}
		else
		{
			InteractibleSlotWidget->RemoveFromViewport();
			IsSlotWidgetDisplayed = false;
		}

		return true;
	}
	else 
		return false;
}

void UInteractionSystemComponent::Interact()
{
	if (InteractibleActors.Num() > 0) {
		IInteractionInterface* Interface = Cast<IInteractionInterface>(InteractibleActors[0]);
		if (Interface)
		{
			Interface->Execute_Interact(InteractibleActors[0], GetOwner());
		}
	}
}

/* Fill SlotWidget with InteractionInfo from the overlapped Object */
void UInteractionSystemComponent::SetupSlotInfo(UInteractibleSlotWidget* SlotWidget, AActor* Object)
{
	if (InteractionDataAsset)
	{
		IInteractionInterface* Interface = Cast<IInteractionInterface>(Object);
		if (Interface) {
			FInteractionDetails Details = Interface->Execute_GetInteractionDetails(Object);
			SlotWidget->InteractibleIcon->SetBrushFromTexture(Details.InteractionIcon);
			SlotWidget->InteractibleTypeName->SetText(FText::FromString(Details.InteractionName));
			SlotWidget->InteractibleTypeName->SetColorAndOpacity(FSlateColor(Details.InteractionNameColor));
			//UE_LOG(LogTemp, Warning, TEXT("Setting up Slot Widget: [%s] %s"), *SlotWidget->GetName(), *Details.InteractionName)
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Interface not casted"))
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("InteractionDataAsset not set"))
}