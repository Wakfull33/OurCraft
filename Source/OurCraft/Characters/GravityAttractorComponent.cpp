// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityAttractorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Generation/PlanetActor.h"


// Sets default values for this component's properties
UGravityAttractorComponent::UGravityAttractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	if(UsePlanetActor)
		Owner = Cast<APlanetActor>(GetOwner());
}


void UGravityAttractorComponent::Attract(AActor* AttractedActor) const
{
	FVector TargetDirection;
	if (UsePlanetActor)
		TargetDirection = (AttractedActor->GetActorLocation() - Owner->PlanetCenter).GetSafeNormal();
	else
		TargetDirection = (AttractedActor->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();

	const FVector Up = AttractedActor->GetActorUpVector();
	
	const FQuat CurrentRot = AttractedActor->GetActorRotation().Quaternion();
	const FQuat LookAt = UKismetMathLibrary::FindLookAtRotation(Up, TargetDirection).Quaternion();
	AttractedActor->SetActorRotation(CurrentRot * LookAt);

	UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(AttractedActor->GetRootComponent());
	Root->AddForce(TargetDirection * Gravity * 100, NAME_None, true);

	DrawDebugDirectionalArrow(GetWorld(), AttractedActor->GetActorLocation(), AttractedActor->GetActorLocation() + (CurrentRot.Vector() * LookAt.Vector() * 100), 10, FColor::Red, false, -1, 0, 5);
	//DrawDebugDirectionalArrow(GetWorld(), AttractedActor->GetActorLocation(), AttractedActor->GetActorLocation() + TargetDirection * Gravity * 100, 10, FColor::Red, false, -1, 0, 5);
	DrawDebugDirectionalArrow(GetWorld(), AttractedActor->GetActorLocation(), AttractedActor->GetActorLocation() + (CurrentRot.Vector() * 100), 10, FColor::Green, false, -1, 0, 5);
	DrawDebugDirectionalArrow(GetWorld(), AttractedActor->GetActorLocation(), AttractedActor->GetActorLocation() + (LookAt.Vector() * 100), 10, FColor::Orange, false, -1, 0, 5);
	//DrawDebugDirectionalArrow(GetWorld(), AttractedActor->GetActorLocation(), AttractedActor->GetActorLocation() + (Up * 100), 10, FColor::Magenta, false, -1, 0, 5);

	UE_LOG(LogTemp, Warning, TEXT("Force To Add: %s"), *(TargetDirection * Gravity * 100).ToCompactString())
}

// Called when the game starts
void UGravityAttractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGravityAttractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

