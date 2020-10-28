// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityActorComponent.h"
#include "GravityAttractorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Generation/PlanetActor.h"

// Sets default values for this component's properties
UGravityActorComponent::UGravityActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravityActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if(UsePlanetActor)
	{
		Planet = Cast<APlanetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), APlanetActor::StaticClass()));

		if (Planet)
		{
			PlanetGravityComponent = Cast<UGravityAttractorComponent>(Planet->GetComponentByClass(UGravityAttractorComponent::StaticClass()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Planet Found !"));
			PlanetGravityComponent = nullptr;
		}
	}
	else
	{
		TArray<AActor*> Planets;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Planet"), Planets);

		UE_LOG(LogTemp, Warning, TEXT("Planets: %d"), Planets.Num())

		if (Planets.Num() > 0)
			PlanetTest = Planets[0];

		if (PlanetTest)
		{
			PlanetGravityComponent = Cast<UGravityAttractorComponent>(PlanetTest->GetComponentByClass(UGravityAttractorComponent::StaticClass()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Planet Found !"));
			PlanetGravityComponent = nullptr;
		}
	}

		
	UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Root->SetSimulatePhysics(true);
	Root->SetEnableGravity(false);
	Root->BodyInstance.bLockRotation = true;
	Root->BodyInstance.bLockXRotation = true;
	Root->BodyInstance.bLockYRotation = true;
	Root->BodyInstance.bLockZRotation = true;
}


// Called every frame
void UGravityActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PlanetGravityComponent)
		PlanetGravityComponent->Attract(GetOwner());
}

