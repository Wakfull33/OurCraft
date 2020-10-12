// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralMeshComponent.h" 
#include "StructUtils.generated.h"


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

UCLASS()
class OURCRAFT_API UStructUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
