// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

bool UInteractibleSlotWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	return true;
}