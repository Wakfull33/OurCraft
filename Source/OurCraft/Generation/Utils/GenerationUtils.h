// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OurCraft/Utils/DelegateUtils.h"
#include "OurCraft/Utils/AsyncTypes.h"

/**
 * 
 */

/*Library class for async task in generation*/
class OURCRAFT_API UGenerationUtils{

public:

	static int EdgeTable[256];

	static int Tritable[256][16];

	static FVector CellPosOffset[7];
	
};
