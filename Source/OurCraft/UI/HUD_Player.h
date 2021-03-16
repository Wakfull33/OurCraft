// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Player.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API AHUD_Player : public AHUD
{
	GENERATED_BODY()
	
public:


private:
	virtual void BeginPlay() override;

	//UPROPERTY()
	//class TSubclassOf<class UInteractibleListWidget> InteractibleListWidgetReference = nullptr;
};
