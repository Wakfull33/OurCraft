// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SphereComponent->SetRelativeLocation(FVector::ZeroVector);
	SphereComponent->SetSphereRadius(200);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnConstruction(const FTransform& Transform)
{
	if(!DataTable.IsNull())
	{
		FItemData Data = *DataTable.GetRow<FItemData>("");
		StaticMeshComponent->SetStaticMesh(Data.StaticMesh);
		ItemData = Data;
	}
}

void AItem::PickupItem(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("BasicPickup from %s triggered by: %s"), *GetName(), *Actor->GetName())
}