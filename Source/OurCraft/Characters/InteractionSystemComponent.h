// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionSystemComponent.generated.h"


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
	class APlayerController* PlayerController = nullptr;

private:

	UPROPERTY()
	class UInventoryDataAsset* InventoryDataAsset = nullptr;

	UPROPERTY()
	class UInteractionDataAsset* InteractionDataAsset = nullptr;

	UPROPERTY()
	class UDataAssetLoadingSubsystem* DataAssetLoader = nullptr;

	UPROPERTY()
	class UInteractibleSlotWidget* InteractibleSlotWidget = nullptr;

	UPROPERTY()
	class AHUD_Player* Hud = nullptr;

	class ACharacter* OwnerCharacter = nullptr;

};
