// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityActorComponent.generated.h"


class APlanetActor;
class UGravityAttractorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURCRAFT_API UGravityActorComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UGravityActorComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Mass = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UsePlanetActor = false;
	
	APlanetActor* Planet;
	AActor* PlanetTest;
	UGravityAttractorComponent* PlanetGravityComponent;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
