// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralMeshComponent.h" 
#include "StructUtils.generated.h"

enum EItemType;

USTRUCT(BlueprintType)
struct FMeshData {
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadWrite)
	TArray<int> Triangles;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> Normals;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> UVs;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FColor> VertexColors;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FProcMeshTangent> Tangents;
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

UCLASS()
class OURCRAFT_API UStructUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};


