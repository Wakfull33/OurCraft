// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetChunkActor.h"
#include "PlanetActor.h"

// Sets default values
APlanetChunkActor::APlanetChunkActor()
{

	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	NewRootComponent->Mobility = EComponentMobility::Movable;
	NewRootComponent->SetWorldTransform(GetActorTransform());
	SetRootComponent(NewRootComponent);
	
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMeshComponent->AttachToComponent(NewRootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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


void APlanetChunkActor::InitialiseChunk(int X, int Y, int Z, int ChunkSideSize, float VoxelSize, APlanetActor * ChunkPlanetOwner){
	ChunkXCoord = X;
	ChunkYCoord = Y;
	ChunkZCoord = Z;
	ChunkSize = ChunkSideSize;
	CellSize = VoxelSize;
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

	FGenerationTaskWork* WorkDelegate = new FGenerationTaskWork();
	FGenerationTaskComplete* CallBackDelegate = new FGenerationTaskComplete();

	WorkDelegate->AddUObject(this, &APlanetChunkActor::GenerateMeshData);
	WorkDelegate->AddUObject(this, &APlanetChunkActor::GenerateDensityField);
	
	CallBackDelegate->AddUObject(this, &APlanetChunkActor::FinishGenerateMeshDataAsync);
	CallBackDelegate->AddUObject(this, &APlanetChunkActor::FinishGenerateDensityFieldAsync);


	FMeshDataResult* TaskResultToFill = new FMeshDataResult();
	
	auto Task = new FAsyncTask<FGenerationAsyncTask>(WorkDelegate, CallBackDelegate, TaskResultToFill);

	PlanetOwner->RegisterTaskForChunkSafe(this, Task);
}

void APlanetChunkActor::GenerateDensityFieldAsync() {
	
	FGenerationTaskWork* WorkDelegate = new FGenerationTaskWork();
	FGenerationTaskComplete* CallBackDelegate = new FGenerationTaskComplete();

	WorkDelegate->AddUObject(this, &APlanetChunkActor::GenerateDensityField);
	CallBackDelegate->AddUObject(this, &APlanetChunkActor::FinishGenerateDensityFieldAsync);
	
	FNoiseDataResult* TaskResultToFill = new FNoiseDataResult();

	auto Task = new FAsyncTask<FGenerationAsyncTask>(WorkDelegate, CallBackDelegate, TaskResultToFill);

	PlanetOwner->RegisterTaskForChunkSafe(this, Task);
}


void APlanetChunkActor::FinishGenerateDensityFieldAsync(FGenerationAsyncResult* NoiseData) {
	//TODO
}


void APlanetChunkActor::GenerateMeshDataAsync() {

	FGenerationTaskWork* WorkDelegate = new FGenerationTaskWork();
	FGenerationTaskComplete* CallBackDelegate = new FGenerationTaskComplete();

	WorkDelegate->AddUObject(this, &APlanetChunkActor::GenerateMeshData);
	CallBackDelegate->AddUObject(this, &APlanetChunkActor::FinishGenerateMeshDataAsync);

	FMeshDataResult* TaskResultToFill = new FMeshDataResult();

	auto Task = new FAsyncTask<FGenerationAsyncTask>(WorkDelegate, CallBackDelegate, TaskResultToFill);

	PlanetOwner->RegisterTaskForChunkSafe(this, Task);
}


void APlanetChunkActor::FinishGenerateMeshDataAsync(FGenerationAsyncResult* MeshData) {
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

void APlanetChunkActor::GenerateDensityField(FGenerationAsyncResult* NoiseData) {
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

void APlanetChunkActor::GenerateMeshData(FGenerationAsyncResult* MeshData) {
	for (int x = 0; x < ChunkSize; x++) {
		for (int y = 0; y < ChunkSize; y++) {
			for (int z = 0; z < ChunkSize; z++) {
				//TODO
			}
		}
	}
}

void APlanetChunkActor::CreateChunkMesh(FMeshDataResult* MeshData) {
	UE_LOG(LogTemp, Warning, TEXT("Create Mesh for chunk X: %d, Y: %d, Z: %d"), ChunkXCoord, ChunkYCoord, ChunkZCoord);
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