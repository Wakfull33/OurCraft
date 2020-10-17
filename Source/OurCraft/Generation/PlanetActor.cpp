// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetActor.h"
#include "PlanetChunkActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlanetActor::APlanetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	NewRootComponent->Mobility = EComponentMobility::Movable;
	NewRootComponent->SetWorldTransform(GetActorTransform());
	SetRootComponent(NewRootComponent);
	
}

// Called when the game starts or when spawned
void APlanetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanetActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void APlanetActor::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	PlanetCenter = GetActorLocation() + Radius * 100;
	
	const float ChunkCentimeterSize = ChunkSize * CellSize;
	const float ChunkMeterSize = ChunkCentimeterSize * 0.01f;
	NumberOfChunkSide = Radius * 2 / ChunkMeterSize;
	NumberOfChunkSide++;
}


void APlanetActor::Generate() {

	PlanetCenter = GetActorLocation() + Radius * 100;

	const float ChunkCentimeterSize = ChunkSize * CellSize;
	const float ChunkMeterSize = ChunkCentimeterSize * 0.01f;
	NumberOfChunkSide = Radius * 2 / ChunkMeterSize;
	NumberOfChunkSide++;

	if (!IsPlanetRunningTasks()) {

		for (auto Chunk : Chunks) {
			if (Chunk != nullptr) {
				GetWorld()->DestroyActor(Chunk);
			}
		}

		Chunks.Empty();

		//const float ChunkCentimeterSize = ChunkSize * CellSize;

		Chunks.Reserve(FMath::Pow(NumberOfChunkSide, 3.0f));

		for (int x = 0; x < NumberOfChunkSide; x++) {
			for (int y = 0; y < NumberOfChunkSide; y++) {
				for (int z = 0; z < NumberOfChunkSide; z++) {

					FVector ChunkSpawnPosition = FVector(x * ChunkCentimeterSize, y * ChunkCentimeterSize, z * ChunkCentimeterSize);
					FRotator ChunkSpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

					APlanetChunkActor* Chunk = GetWorld()->SpawnActor<APlanetChunkActor>(ChunkSpawnPosition, ChunkSpawnRotation);
					Chunks.Add(Chunk);
					Chunk->InitialiseChunk(x, y, z, ChunkSize, CellSize, this);
					Chunk->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				}
			}
		}

		AsyncTaskRegistry.Empty();
		AsyncTaskRegistry.Reserve(FMath::Pow(NumberOfChunkSide, 3.0f));
		for (auto Chunk: Chunks) {
			AsyncTaskRegistry.Add(TPairInitializer<APlanetChunkActor*, FAsyncTask<FGenerationAsyncTask>*>(Chunk, nullptr));
		}

		//TODO Need to generate chunk under player pos first
		for (auto Chunk : Chunks) {
			Chunk->GenerateChunkAsync();
		}
		
	}
	
}

void APlanetActor::GenerateNewSeed(){

	//TODO calc new seed
	
	Generate();
}


bool APlanetActor::IsPlanetRunningTasks() const {

	bool RunningTasks = false;
	for (auto& Task : AsyncTaskRegistry) {
		if (Task.Value != nullptr) {
			RunningTasks = true;
			break;
		}
	}
	return RunningTasks;
}

bool APlanetActor::IsChunkRunningTask(APlanetChunkActor* Chunk) const {

	bool ChunkAlreadyRunning = false;
	
	const int Index = Chunk->ChunkXCoord * FMath::Square(NumberOfChunkSide) + Chunk->ChunkYCoord * NumberOfChunkSide + Chunk->ChunkZCoord;
	auto& AsyncTask = AsyncTaskRegistry[Index];

	if (Chunk != AsyncTask.Key) {
		//TODO register invalid restore it
	}

	ChunkAlreadyRunning = AsyncTask.Value != nullptr;
	return ChunkAlreadyRunning;
	
}

void APlanetActor::RegisterTaskForChunkUnSafe(APlanetChunkActor* Chunk, FAsyncTask<FGenerationAsyncTask>* Task) {

	const int Index = Chunk->ChunkXCoord * FMath::Square(NumberOfChunkSide) + Chunk->ChunkYCoord * NumberOfChunkSide + Chunk->ChunkZCoord;
	auto& AsyncTask = AsyncTaskRegistry[Index];

	if (Chunk != AsyncTask.Key) {
		//TODO register invalid restore it
	}

	AsyncTask.Value = Task;
	Task->StartBackgroundTask();
}


void APlanetActor::ResetTaskForChunk(APlanetChunkActor* Chunk) {
	const int Index = Chunk->ChunkXCoord * FMath::Square(NumberOfChunkSide) + Chunk->ChunkYCoord * NumberOfChunkSide + Chunk->ChunkZCoord;
	auto& AsyncTask = AsyncTaskRegistry[Index];
	AsyncTask.Value = nullptr;
}


void APlanetActor::RegisterTaskForChunkSafe(APlanetChunkActor* Chunk, FAsyncTask<FGenerationAsyncTask>* Task) {

	if (Chunk != nullptr && Task != nullptr) {
		if(!IsChunkRunningTask(Chunk)) {
			RegisterTaskForChunkUnSafe(Chunk, Task);
		}
	}
}

void APlanetActor::DrawDebugPlanet() {
	DrawDebugSphere(GetWorld(), PlanetCenter, Radius * 100.0f, 50, FColor::Red, false, 20.0f, 0.0f, 10.0f);
}
