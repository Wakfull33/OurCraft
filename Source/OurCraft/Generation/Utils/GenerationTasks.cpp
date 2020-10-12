// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationTasks.h"
#include "OurCraft/Generation/PlanetChunkActor.h"

void UGenerationTasks::GenerateDensityFieldForChunkAsync(APlanetChunkActor* TargetChunk, FDensityFieldGenerationTaskComplete* CallBackFunction) {

	if (TargetChunk != nullptr) {
		auto Task = new FAsyncTask<FChunkDensityFieldGenerationAsyncTask>(TargetChunk, CallBackFunction);
		Task->StartBackgroundTask();
	}
	
}


void UGenerationTasks::GenerateMeshDataForChunkAsync(APlanetChunkActor* TargetChunk, FMeshDataGenerationTaskComplete* CallBackFunction) {

	if (TargetChunk != nullptr) {
		auto Task = new FAsyncTask<FChunkMeshDataGenerationAsyncTask>(TargetChunk, CallBackFunction);
		Task->StartBackgroundTask();
	}
	
}
