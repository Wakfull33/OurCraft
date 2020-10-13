// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils.h"
#include "DelegateUtils.h"

class APlanetChunkActor;
class APlanetActor;


/*@Class for creating in asynchronous way density field of a chunk, this class is FNonAbandonableTask because it cannot be stoped or paused*/
class OURCRAFT_API FGenerationAsyncTask : public FNonAbandonableTask {

public:

	FGenerationTaskWork* WorkDelegate = nullptr;
	FGenerationTaskComplete* CallBackDelegate = nullptr;

private:
	
	FGenerationAsyncResult* ResultData = nullptr;
	
public:

	FGenerationAsyncTask(FGenerationTaskWork* Work, FGenerationTaskComplete* CallBack, FGenerationAsyncResult* ObjectForContainsResults);

	FORCEINLINE TStatId GetStatId() const;
	void DoWork();
	
};
