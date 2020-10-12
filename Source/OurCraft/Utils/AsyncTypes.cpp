// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTypes.h"
#include "OurCraft/Generation/PlanetChunkActor.h"

FChunkDensityFieldGenerationAsyncTask::FChunkDensityFieldGenerationAsyncTask(APlanetChunkActor* TargetChunk, FDensityFieldGenerationTaskComplete* CallBack) {
	PlanetChunk = TargetChunk;
	EndEventCallBack = CallBack;
}


void FChunkDensityFieldGenerationAsyncTask::DoWork() {

	PlanetChunk->GenerateDensityField();
	if (EndEventCallBack->IsBound()) {
		//Work is complete, callback to GameThread
		AsyncTask(ENamedThreads::GameThread, [this] {EndEventCallBack->Execute(); });
	}
}

TStatId FChunkDensityFieldGenerationAsyncTask::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(FChunkDensityFieldGenerationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
}

FChunkMeshDataGenerationAsyncTask::FChunkMeshDataGenerationAsyncTask(APlanetChunkActor* TargetChunk, FMeshDataGenerationTaskComplete* CallBack) {
	PlanetChunk = TargetChunk;
	EndEventCallBack = CallBack;
}

void FChunkMeshDataGenerationAsyncTask::DoWork() {

	MeshData = FMeshData();
	PlanetChunk->GenerateMeshData(MeshData);
	if (EndEventCallBack->IsBound()) {
		//Work is complete, callback to GameThread
		AsyncTask(ENamedThreads::GameThread, [this]() {EndEventCallBack->Execute(MeshData); });
	}
}

TStatId FChunkMeshDataGenerationAsyncTask::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(FChunkMeshDataGenerationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
}
