// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils.h"
#include "DelegateUtils.h"

class APlanetChunkActor;
class APlanetActor;

/*@Class for creating in asynchronous way density field of a chunk, this class is FNonAbandonableTask because it cannot be stoped or paused*/
class OURCRAFT_API FChunkDensityFieldGenerationAsyncTask : public FNonAbandonableTask {

public:

	APlanetChunkActor* PlanetChunk = nullptr;
	
private:
	
	FDensityFieldGenerationTaskComplete* EndEventCallBack = nullptr;
	
public:

	FChunkDensityFieldGenerationAsyncTask(APlanetChunkActor* TargetChunk, FDensityFieldGenerationTaskComplete* CallBack = nullptr);

	FORCEINLINE TStatId GetStatId() const;
	void DoWork();
	
};

/*@Class for creating in asynchronous way mesh data of a chunk, this class is FNonAbandonableTask because it cannot be stoped or paused*/
class OURCRAFT_API FChunkMeshDataGenerationAsyncTask : public FNonAbandonableTask {

public:

	APlanetChunkActor* PlanetChunk = nullptr;

private:

	FMeshData MeshData;
	FMeshDataGenerationTaskComplete* EndEventCallBack = nullptr;

public:

	FChunkMeshDataGenerationAsyncTask(APlanetChunkActor* TargetChunk, FMeshDataGenerationTaskComplete* CallBack = nullptr);

	FORCEINLINE TStatId GetStatId() const;
	void DoWork();
	
};