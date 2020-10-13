// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralMeshComponent.h" 
#include "Engine/DataTable.h"
#include "StructUtils.generated.h"

enum EItemType;
class APlanetChunkActor;

USTRUCT()
struct FGenerationAsyncResult {
	
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FMeshDataResult : public FGenerationAsyncResult {
	
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

USTRUCT()
struct FNoiseDataResult : public FGenerationAsyncResult {
	GENERATED_BODY()
	
};

#pragma region Items Structs

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName = "Default Name";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemDescription = "Default Description";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemMeshPath = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemIcon = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemValue = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemType;
};

#pragma endregion 

UCLASS()
class OURCRAFT_API UStructUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};


