// Fill out your copyright notice in the Description page of Project Settings.


#include "GravitySetterComponent.h"

#include "MainCharacter.h"
#include "Components/ShapeComponent.h"
#include "PlanetaryMovementComponent.h"

// Sets default values for this component's properties
UGravitySetterComponent::UGravitySetterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravitySetterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...


	TArray<UShapeComponent*> Comps;

	if (GetOwner() != nullptr)
	{
		GetOwner()->GetComponents(Comps);
		if (Comps.Num() > 0)
		{
			ShapeComponent = Comps[0];
			UE_LOG(LogTemp, Warning, TEXT("ShapeComponent Found: %s"), *ShapeComponent->GetName())
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No ShapeComponent Found"))
		}
	}

	if(ShapeComponent)
	{
	    
		ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &UGravitySetterComponent::OnGravitySetterComponentOverlapBegin);
		ShapeComponent->OnComponentEndOverlap.AddDynamic(this, &UGravitySetterComponent::OnGravitySetterComponentOverlapEnd);
	}
	
}

void UGravitySetterComponent::PostInitProperties()
{
	Super::PostInitProperties();

}


// Called every frame
void UGravitySetterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGravitySetterComponent::OnGravitySetterComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);

	if(Character != nullptr)
	{
		Character->SetupGravity(this);
		UE_LOG(LogTemp, Warning, TEXT("[%s] Overlapped: %s    UpVector: %s"), *GetName(), *GetOwner()->GetName(), *GetOwner()->GetActorUpVector().ToString())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to cast MainCharacter"))
	}
}

void  UGravitySetterComponent::OnGravitySetterComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


