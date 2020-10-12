// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTypes.h"

FChunkDensityFieldGenerationAsyncTask::FChunkDensityFieldGenerationAsyncTask(APlanetChunkActor* TargetChunk, FDensityFieldGenerationTaskComplete* CallBack) {
	PlanetChunk = TargetChunk;
	EndEventCallBack = CallBack;
}


void FChunkDensityFieldGenerationAsyncTask::DoWork() {

	//TODO generate noise field

	if (EndEventCallBack->IsBound()) {
		//Work is complete, callback to GameThread
		const TFunction<void()> FuncCallBack = [this] {EndEventCallBack->Execute(); };
		AsyncTask(ENamedThreads::GameThread, FuncCallBack);
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
	//TODO compute mesh data
	
	if (EndEventCallBack->IsBound()) {
		AsyncTask(ENamedThreads::GameThread, [this]() {EndEventCallBack->Execute(MeshData); });
	}
}

TStatId FChunkMeshDataGenerationAsyncTask::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(FChunkMeshDataGenerationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
}
