// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityAttractorComponent.generated.h"


class APlanetActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURCRAFT_API UGravityAttractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGravityAttractorComponent();

	APlanetActor* Owner;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UsePlanetActor = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gravity = -10.f;

	UFUNCTION(BlueprintCallable)
	void Attract(AActor* AttractedActor) const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
