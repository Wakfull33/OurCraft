// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Utils/StructUtils.h"
#include "InteractionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API UInteractionDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInteractionDetails InteractionTalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInteractionDetails InteractionUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInteractionDetails InteractionPickUp;
};
