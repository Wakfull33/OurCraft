// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OurCraft/Utils/StructUtils.h"
#include "OurCraft/Utils/DelegateUtils.h"
#include "OurCraft/Generation/Utils/GenerationTasks.h"
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
	APlanetActor* PlanetOwner;

	UPROPERTY()
	TArray<float> DensityField;

	UPROPERTY()
	UProceduralMeshComponent* ProceduralMeshComponent;
	
private:


public:

	APlanetChunkActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitialiseChunk(int X, int Y, int Z, int ChunkSideSize, APlanetActor* ChunkPlanetOwner);


	void GenerateChunkAsync();
	void GenerateDensityFieldAsync();
	void GenerateDensityFieldAsync(FDensityFieldGenerationTaskComplete* Delegate);
	void GenerateMeshDataAsync();
	void GenerateMeshDataAsync(FMeshDataGenerationTaskComplete* Delegate);
	
	void GenerateDensityField();
	void FinishGenerateDensityFieldAsync();
	void GenerateMeshData(FMeshData& MeshData);
	void FinishGenerateMeshDataAsync(FMeshData& MeshData);
	
	void CreateChunkMesh(FMeshData& MeshData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
