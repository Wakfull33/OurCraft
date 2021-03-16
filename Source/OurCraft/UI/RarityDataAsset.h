// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RarityDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API URarityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ColorCommon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ColorRare;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ColorEpic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ColorLegendary;

};
