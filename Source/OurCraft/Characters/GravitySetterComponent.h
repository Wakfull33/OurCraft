// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OurCraft/Utils/EnumsUtils.h"

#include "GravitySetterComponent.generated.h"

class UShapeComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURCRAFT_API UGravitySetterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGravitySetterComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ShapeCollision")
	UShapeComponent* ShapeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ShapeCollision")
	TEnumAsByte<EGravityType> GravityType;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void PostInitProperties() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void OnGravitySetterComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnGravitySetterComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};