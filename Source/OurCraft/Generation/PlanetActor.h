// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OurCraft/Utils/StructUtils.h"
#include "OurCraft/Utils/AsyncTypes.h"
#include "PlanetActor.generated.h"

class APlanetChunkActor;

UCLASS()
class OURCRAFT_API APlanetActor : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, Category = "Planet settings", meta = (tooltip = "Radius in meters"))
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Planet settings", meta = (tooltip = "Number of voxels on a chunk side"))
	int ChunkSize = 32;

	UPROPERTY(EditAnywhere, Category = "Planet settings", meta = (tooltip = "Size of a voxel in cm"))
	float CellSize = 64.0f;

	UPROPERTY(VisibleAnywhere, Category = "Planet settings")
	FVector PlanetCenter;

	UPROPERTY(VisibleAnywhere, Category = "Planet settings")
	int NumberOfChunkSide;
	
	UPROPERTY(VisibleAnywhere, Category = "Planet chunks")
	TArray<APlanetChunkActor*> Chunks;

	TArray<TPair<APlanetChunkActor*, FAsyncTask<FGenerationAsyncTask>*>> AsyncTaskRegistry;
	
private:

	UPROPERTY()
	float Seed;

public:	

	// Sets default values for this actor's properties
	APlanetActor();

	UFUNCTION(CallInEditor, Category = "Actions")
	void Generate();

	UFUNCTION(CallInEditor, Category = "Actions")
	void GenerateNewSeed();

	bool IsPlanetRunningTasks() const;
	bool IsChunkRunningTask(APlanetChunkActor* Chunk) const;
	void RegisterTaskForChunkUnSafe(APlanetChunkActor* Chunk, FAsyncTask<FGenerationAsyncTask>* Task);
	void RegisterTaskForChunkSafe(APlanetChunkActor* Chunk, FAsyncTask<FGenerationAsyncTask>* Task);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
