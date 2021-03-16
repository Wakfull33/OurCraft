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
	FString Description = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxStack = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EItemType> Type;

	FORCEINLINE FItemData operator=(const FItemData& other) 
	{
		Name = other.Name;
		Description = other.Description;
		StaticMesh = other.StaticMesh;
		Icon = other.Icon;
		Value = other.Value;
		MaxStack = other.MaxStack;
		Type = other.Type;

		return *this;
	}

	FORCEINLINE bool operator==(const FItemData& Other) const
	{
		return (Name == Other.Name && Description == Other.Description && StaticMesh == Other.StaticMesh &&	Icon == Other.Icon && Value == Other.Value && Type == Other.Type && MaxStack == Other.MaxStack);
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

	FORCEINLINE bool operator== (const FItemStack& Other) const
	{
		return ItemData == Other.ItemData;
	}

	FItemStack(){};

	FItemStack(const FItemData& _ItemData, int _Count) {
		ItemData = _ItemData;
		ItemCount = _Count;
	};
};

USTRUCT(BlueprintType)
struct FWeaponData : public FItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WeaponDamage;
};

#pragma endregion 

#pragma region Interactions Structs

USTRUCT(BlueprintType)
struct FInteractionDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InteractionIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InteractionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor InteractionNameColor = FLinearColor(0.43f, 0.43f, 0.43f, 1.0f);
};

#pragma endregion

UCLASS()
class OURCRAFT_API UStructUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal FItemStack", CompactNodeTitle = "==", Keywords = "== equals"), Category = "Math")
	static bool EqualEqual_FItemStackFItemStack(const FItemStack& item1, const FItemStack& item2);
	
};


