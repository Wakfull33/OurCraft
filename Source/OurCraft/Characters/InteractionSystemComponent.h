// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionSystemComponent.generated.h"

#pragma region Forward Declarations

class APlayerController;
class UInventoryDataAsset;
class UInteractionDataAsset;
class UDataAssetLoadingSubsystem;
class UInteractibleSlotWidget;
class UInteractibleSlotWidget;
class AHUD_Player;
class ACharacter;

#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURCRAFT_API UInteractionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> InteractibleActors;

	UPROPERTY()
	bool IsSlotWidgetDisplayed;

	UFUNCTION(BlueprintCallable)
	bool AddObject(AActor* Object);

	UFUNCTION(BlueprintCallable)
	bool RemoveObject(AActor* Object);

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION()
	void SetupSlotInfo(UInteractibleSlotWidget* SlotWidget, AActor* Object);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerController* PlayerController = nullptr;

private:

	UPROPERTY()
	UInventoryDataAsset* InventoryDataAsset = nullptr;

	UPROPERTY()
	UInteractionDataAsset* InteractionDataAsset = nullptr;

	UPROPERTY()
	UDataAssetLoadingSubsystem* DataAssetLoader = nullptr;

	UPROPERTY()
	UInteractibleSlotWidget* InteractibleSlotWidget = nullptr;

	UPROPERTY()
	AHUD_Player* Hud = nullptr;

	UPROPERTY()
	ACharacter* OwnerCharacter = nullptr;

};
