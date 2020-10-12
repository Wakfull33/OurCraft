// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructUtils.generated.h"

/**
 * 
 */

enum EItemType;

UCLASS()
class OURCRAFT_API UStructUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

#pragma region Items Structs

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString ItemName = "Default Name";

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString ItemDescription = "Default Description";

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString ItemMeshPath = "";

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString ItemIcon = "";

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int ItemValue = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString ItemType;
};


#pragma endregion 
