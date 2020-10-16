// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralMeshComponent.h" 
#include "Engine/DataTable.h"
#include "EnumsUtils.h"
#include "StructUtils.generated.h"

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
	FString Name = "Default Name";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Description = "Default Description";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EItemType> Type;

	FItemData operator=(const FItemData& other) {
		Name = other.Name;
		Description = other.Description;
		StaticMesh = other.StaticMesh;
		Icon = other.Icon;
		Value = other.Value;
		Type = other.Type;

		return *this;
	}
};

USTRUCT(BlueprintType)
struct FItemStack
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FItemData ItemData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemCount;
};


#pragma endregion 

UCLASS()
class OURCRAFT_API UStructUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};


