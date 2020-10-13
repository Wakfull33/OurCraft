// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FGenerationTaskWork, FGenerationAsyncResult*);
DECLARE_MULTICAST_DELEGATE_OneParam(FGenerationTaskComplete, FGenerationAsyncResult*);

