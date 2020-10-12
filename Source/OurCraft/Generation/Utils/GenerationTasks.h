// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OurCraft/Utils/DelegateUtils.h"
#include "OurCraft/Utils/AsyncTypes.h"

/**
 * 
 */

class APlanetChunkActor;

/*Library class for async task in generation*/
class OURCRAFT_API UGenerationTasks{

	static void GenerateDensityFieldForChunkAsync(APlanetChunkActor* TargetChunk, FDensityFieldGenerationTaskComplete* CallBackFunction = nullptr);
	
	static void GenerateMeshDataForChunkAsync(APlanetChunkActor* TargetChunk, FMeshDataGenerationTaskComplete* CallBackFunction = nullptr);
};
