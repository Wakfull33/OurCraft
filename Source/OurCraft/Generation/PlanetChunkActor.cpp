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

void APlanetChunkActor::StartGenerateDensityFieldAsync() {
	//TODO
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

void APlanetChunkActor::StartGenerateMeshDataFieldAsync() {
	//TODO
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
	const FVector PlanetCenter = PlanetOwner->PlanetCenter;
	const float PlanetRadius = PlanetOwner->Radius;
	const bool Planet = PlanetOwner->Planet;
	
	for (int x = 0 ; x < ChunkSize; x++) {
		for (int y = 0; y < ChunkSize; y++) {
			for (int z = 0; z < ChunkSize; z++) {
				float NoiseValue = 0.0f;
				if (Planet) {
					const float DistCellToPlanetCenter = FVector::Dist(PointToWorldPos(x, y, z, true), PlanetCenter);
					NoiseValue = DistCellToPlanetCenter - PlanetRadius;
				}
				else {
					NoiseValue = PointToWorldPos(x, y, z, true).Z > PlanetCenter.Z ? 1.0f : -1.0f;
				}
				DensityField.Add(NoiseValue);
			}
		}
	}
	
}

void APlanetChunkActor::GenerateMeshData(FGenerationAsyncResult* MeshData) {

	const int NumberOfElementsInChunk = FMath::Pow(ChunkSize, 3.0f);
	const bool Smooth = PlanetOwner->SmoothTerrain;
	
	if (DensityField.Num() == NumberOfElementsInChunk) {

		const float IsoValue = PlanetOwner->IsoValue;
		
		for (int x = 0; x < ChunkSize; x++) {
			for (int y = 0; y < ChunkSize; y++) {
				for (int z = 0; z < ChunkSize; z++) {
					PolygoniseCell(x, y, z, IsoValue, (FMeshDataResult*)MeshData, Smooth);
				}
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Density field invalid"));
	}

}

void APlanetChunkActor::CreateChunkMesh(FMeshDataResult* MeshData) {
	UE_LOG(LogTemp, Warning, TEXT("Create Mesh for chunk X: %d, Y: %d, Z: %d"), ChunkXCoord, ChunkYCoord, ChunkZCoord);

	delete MeshData;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/


void APlanetChunkActor::PolygoniseCell(int x, int y, int z, float IsoValue, FMeshDataResult* MeshData, bool Smooth){
	TArray<float> CellValues = TArray<float>();	
	TArray<FVector> CellPointsPosition = TArray<FVector>();
	
	GetCellValues(x, y, z, CellValues);
	GetCellPointsValues(x, y, z, false, CellPointsPosition);

	int CellIndex = 0;
	for (int i = 0; i < CellValues.Num(); i++) {
		if (CellValues[i] < IsoValue) {
			CellIndex += FMath::Pow(2, i);
		}
	}

	if (CellIndex != 0) {

		int VerticesNum = MeshData->Vertices.Num();
		int NormalsNum = MeshData->Normals.Num();
		
		FVector TriTableVertices[12];

		int TriTableVerticesIndex[12];
		int TriTableNormalsIndex[12];
		
		bool TriTableVerticesAlreadyAdded[12] = { false };
		
		if (UGenerationUtils::EdgeTable[CellIndex] & 1){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[0], CellValues[0]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[1], CellValues[1]);
			TriTableVertices[0] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 2){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[1], CellValues[1]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[2], CellValues[2]);
			TriTableVertices[1] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 4){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[2], CellValues[2]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[3], CellValues[3]);
			TriTableVertices[2] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 8){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[0], CellValues[0]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[3], CellValues[3]);
			TriTableVertices[3] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 16){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[4], CellValues[4]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[5], CellValues[5]);
			TriTableVertices[4] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 32){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[5], CellValues[5]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[6], CellValues[6]);
			TriTableVertices[5] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 64){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[6], CellValues[6]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[7], CellValues[7]);
			TriTableVertices[6] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 128){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[7], CellValues[7]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[4], CellValues[4]);
			TriTableVertices[7] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 256){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[0], CellValues[0]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[4], CellValues[4]);
			TriTableVertices[8] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 512){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[1], CellValues[1]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[5], CellValues[5]);
			TriTableVertices[9] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 1024){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[2], CellValues[2]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[6], CellValues[6]);
			TriTableVertices[10] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}
		if (UGenerationUtils::EdgeTable[CellIndex] & 2048){
			TPair<FVector, float> VoxelA = TPairInitializer<FVector, float>(CellPointsPosition[3], CellValues[3]);
			TPair<FVector, float> VoxelB = TPairInitializer<FVector, float>(CellPointsPosition[7], CellValues[7]);
			TriTableVertices[11] = ComputeVertice(VoxelA, VoxelB, IsoValue, Smooth);
		}

		for (size_t i = 0; UGenerationUtils::Tritable[CellIndex][i] != -1; i += 3) {

			FVector Vertice1 = TriTableVertices[UGenerationUtils::Tritable[CellIndex][i]];
			FVector Vertice2 = TriTableVertices[UGenerationUtils::Tritable[CellIndex][i + 1]];
			FVector Vertice3 = TriTableVertices[UGenerationUtils::Tritable[CellIndex][i + 2]];

			FVector AB(Vertice2.X - Vertice1.X, Vertice2.Y - Vertice1.Y, Vertice2.Z - Vertice1.Z);
			FVector AC(Vertice3.X - Vertice1.X, Vertice3.Y - Vertice1.Y, Vertice3.Z - Vertice1.Z);
			FVector NormaleTriangle = AB ^ AC;
			NormaleTriangle.Normalize(1.0f);
			
			for (int j = 0; j < 3; j++) {
				
				const int TritableIndex = UGenerationUtils::Tritable[CellIndex][i + j];
				
				if (!TriTableVerticesAlreadyAdded[TritableIndex]) {
					
					TriTableVerticesAlreadyAdded[TritableIndex] = true;
	
					MeshData->Vertices.Add(TriTableVertices[TritableIndex]);
					TriTableVerticesIndex[TritableIndex] = VerticesNum;

					MeshData->Normals.Add(-NormaleTriangle);
					TriTableNormalsIndex[TritableIndex] = NormalsNum;
					
					MeshData->Triangles.Add(VerticesNum);

					NormalsNum++;
					VerticesNum++;
				}
				else {
					FVector SmoothedNormal = MeshData->Normals[TriTableNormalsIndex[TritableIndex]] + (-NormaleTriangle);
					SmoothedNormal.Normalize(0.1f);
					MeshData->Normals[TriTableNormalsIndex[TritableIndex]] = SmoothedNormal;

					MeshData->Triangles.Add(TriTableVerticesIndex[TritableIndex]);
				}	
			}
		}
	}
}



void APlanetChunkActor::GetCellValues(int x, int y, int z, TArray<float>& Values) {
	Values.Empty();
	Values.Reserve(8);
	Values.Add(GetPointValue(x, y, z));
	for (auto& Offset :UGenerationUtils::CellPosOffset) {
		Values.Add(GetPointValue(x + Offset.X, y + Offset.Y, z + Offset.Z));
	}
}

void APlanetChunkActor::GetCellPointsValues(int x, int y, int z, bool WorldPos, TArray<FVector>& Values) const{
	Values.Empty();
	Values.Reserve(8);
	Values.Add(PointToWorldPos(x, y, z, WorldPos));
	for (auto& Offset : UGenerationUtils::CellPosOffset) {
		Values.Add(PointToWorldPos(x + Offset.X, y + Offset.Y, z + Offset.Z, WorldPos));
	}
}


float APlanetChunkActor::GetPointValue(int x, int y, int z) {
	return DensityField[x * FMath::Square(ChunkSize) + y * ChunkSize + z];
}

FVector APlanetChunkActor::PointToWorldPos(int x, int y, int z, bool WorldPos) const {
	FVector PointPos = FVector(x * CellSize, y * CellSize, z * CellSize);
	if (WorldPos) {
		PointPos += GetActorLocation();
	}
	return PointPos;
}

FVector APlanetChunkActor::ComputeVertice(TPair<FVector, float>& VoxelA, TPair<FVector, float>& VoxelB, float IsoValue, bool Interp) const{
	FVector Vertice = FVector();
	if (Interp) {
		if (FMath::Abs(IsoValue - VoxelA.Value) < 0.000001f){
			return VoxelA.Key;
		}
		if (FMath::Abs(IsoValue - VoxelB.Value) < 0.000001f){
			return VoxelB.Key;
		}
		if (FMath::Abs(VoxelA.Value - VoxelB.Value) < 0.000001f){
			return VoxelA.Key;
		}
		float mu = (IsoValue - VoxelA.Value) / (VoxelB.Value - VoxelA.Value);
		Vertice.X = VoxelA.Key.X + mu * (VoxelB.Key.X - VoxelA.Key.X);
		Vertice.Y = VoxelA.Key.Y + mu * (VoxelB.Key.Y - VoxelA.Key.Y);
		Vertice.Z = VoxelA.Key.Z + mu * (VoxelB.Key.Z - VoxelA.Key.Z);
	}
	else {
		Vertice = VoxelA.Key + (VoxelB.Key - VoxelA.Key) * 0.5f;
	}
	return Vertice;
}


bool APlanetChunkActor::IsDoingAsyncWork() {
	return PlanetOwner->IsChunkRunningTask(this);
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