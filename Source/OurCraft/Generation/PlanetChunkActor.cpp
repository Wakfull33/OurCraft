// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetChunkActor.h"

// Sets default values
APlanetChunkActor::APlanetChunkActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlanetChunkActor::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void APlanetChunkActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void APlanetChunkActor::InitialiseChunk(int X, int Y, int Z, int ChunkSideSize, APlanetActor * ChunkPlanetOwner){
	ChunkXCoord = X;
	ChunkYCoord = Y;
	ChunkZCoord = Z;
	ChunkSize = ChunkSideSize;
	PlanetOwner = ChunkPlanetOwner;
}

#pragma region Chunk Generation Async Methods

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*****************************CHUNK GENERATION ASYNC METHODS***********************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

void APlanetChunkActor::GenerateChunkAsync() {
	FDensityFieldGenerationTaskComplete* Delegate = new FDensityFieldGenerationTaskComplete();
	Delegate->BindUObject(this, &APlanetChunkActor::FinishGenerateDensityFieldAsync);
	Delegate->BindUObject(this, &APlanetChunkActor::GenerateMeshDataAsync);
	GenerateDensityFieldAsync(Delegate);
}


void APlanetChunkActor::GenerateDensityFieldAsync() {
	FDensityFieldGenerationTaskComplete* Delegate = new FDensityFieldGenerationTaskComplete();
	Delegate->BindUObject(this, &APlanetChunkActor::FinishGenerateDensityFieldAsync);
	GenerateDensityFieldAsync(Delegate);
}
void APlanetChunkActor::GenerateDensityFieldAsync(FDensityFieldGenerationTaskComplete* Delegate) {
	UE_LOG(LogTemp, Warning, TEXT("Density field generation started for chunk X: %d, Y: %d, Z: %d"), ChunkXCoord, ChunkYCoord, ChunkZCoord);
	UGenerationTasks::GenerateDensityFieldForChunkAsync(this, Delegate);
}
void APlanetChunkActor::FinishGenerateDensityFieldAsync() {
	UE_LOG(LogTemp, Warning, TEXT("Density field generation finished for chunk X: %d, Y: %d, Z: %d"), ChunkXCoord, ChunkYCoord, ChunkZCoord);
	//TODO
}


void APlanetChunkActor::GenerateMeshDataAsync() {
	FMeshDataGenerationTaskComplete* Delegate = new FMeshDataGenerationTaskComplete();
	Delegate->BindUObject(this, &APlanetChunkActor::FinishGenerateMeshDataAsync);
	GenerateMeshDataAsync(Delegate);
}
void APlanetChunkActor::GenerateMeshDataAsync(FMeshDataGenerationTaskComplete* Delegate) {
	UE_LOG(LogTemp, Warning, TEXT("Mesh Data generation started for chunk X: %d, Y: %d, Z: %d"), ChunkXCoord, ChunkYCoord, ChunkZCoord);
	UGenerationTasks::GenerateMeshDataForChunkAsync(this, Delegate);
}
void APlanetChunkActor::FinishGenerateMeshDataAsync(FMeshData& MeshData) {
	UE_LOG(LogTemp, Warning, TEXT("Mesh Data generation finished for chunk X: %d, Y: %d, Z: %d"), ChunkXCoord, ChunkYCoord, ChunkZCoord);
	//TODO
}

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

#pragma endregion 

#pragma region  Chunk Generation Methods


/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/********************************CHUNK GENERATION METHODS**************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

void APlanetChunkActor::GenerateDensityField() {

	DensityField.Empty();
	DensityField.Reserve(FMath::Pow(ChunkSize, 3));
	for (int x = 0 ; x < ChunkSize; x++) {
		for (int y = 0; y < ChunkSize; y++) {
			for (int z = 0; z < ChunkSize; z++) {
				//TODO
			}
		}
	}
	
}

void APlanetChunkActor::GenerateMeshData(FMeshData& MeshData) {
	
	for (int x = 0; x < ChunkSize; x++) {
		for (int y = 0; y < ChunkSize; y++) {
			for (int z = 0; z < ChunkSize; z++) {
				//TODO
			}
		}
	}
}

void APlanetChunkActor::CreateChunkMesh(FMeshData& MeshData) {
	
}

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

#pragma endregion 