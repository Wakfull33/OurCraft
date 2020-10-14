// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OurCraft/Utils/StructUtils.h"
#include "OurCraft/Utils/DelegateUtils.h"
#include "OurCraft/Generation/Utils/GenerationUtils.h"
#include "ProceduralMeshComponent.h"
#include "PlanetChunkActor.generated.h"

class APlanetActor;

UCLASS()
class OURCRAFT_API APlanetChunkActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
	int ChunkXCoord;

	UPROPERTY()
	int ChunkYCoord;

	UPROPERTY()
	int ChunkZCoord;

	UPROPERTY()
	int ChunkSize;

	UPROPERTY()
	float CellSize;

	UPROPERTY()
	APlanetActor* PlanetOwner;

	UPROPERTY(VisibleAnywhere)
	TArray<float> DensityField;

	UPROPERTY()
	UProceduralMeshComponent* ProceduralMeshComponent;
	
private:


public:

	APlanetChunkActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitialiseChunk(int X, int Y, int Z, int ChunkSideSize, float VoxelSize, APlanetActor* ChunkPlanetOwner);


	void GenerateChunkAsync();
	void GenerateDensityFieldAsync();
	void GenerateMeshDataAsync();

	void StartGenerateDensityFieldAsync();
	void GenerateDensityField(FGenerationAsyncResult* NoiseData);
	void FinishGenerateDensityFieldAsync(FGenerationAsyncResult* NoiseData);
	void StartGenerateMeshDataFieldAsync();
	void GenerateMeshData(FGenerationAsyncResult* MeshData);
	void FinishGenerateMeshDataAsync(FGenerationAsyncResult* MeshData);
	
	void CreateChunkMesh(FMeshDataResult* MeshData);

	FVector PointToWorldPos(int x, int y, int z, bool WorldPos) const;
	
	float GetPointValue(int x, int y, int z);
	
	void GetCellValues(int x, int y, int z, TArray<float>& Values);
	void GetCellPointsValues(int x, int y, int z, bool WorldPos, TArray<FVector>& Values) const ;
	
	void PolygoniseCell(int x, int y, int z, float IsoValue, FMeshDataResult* MeshData, bool Smooth);

	FVector ComputeVertice(TPair<FVector, float>& VoxelA, TPair<FVector, float>& VoxelB, float IsoValue,bool Interp) const;
	
	bool IsDoingAsyncWork();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
