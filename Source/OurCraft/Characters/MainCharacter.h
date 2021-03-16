// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OurCraft/Utils/StructUtils.h"
#include "MainCharacter.generated.h"

class UGravityActorComponent;
class UGravitySetterComponent;
class UPlanetaryMovementComponent;

UCLASS(config = Game)
class AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	
	AMainCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gravity)
	UGravityActorComponent* GravityActorComponent;

	UFUNCTION()
	void SetupGravity(UGravitySetterComponent* GravitySetter);



	TArray<FItemStack> Inventory;


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for controller yaw input */
	void Turn(float Value);

	/** Called for controller pitch */
	void LookUp(float Value);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void Tick(float DeltaSeconds) override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class UInventorySystemComponent* GetInventorySystem() const { return InventorySystemComponent; }

	FORCEINLINE class UInteractionSystemComponent* GetInteractionSystem() const { return InteractionSystemComponent; }

	UPlanetaryMovementComponent* GetPlanetaryMovementComponent() const;

	UGravitySetterComponent* GravitySetterComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventorySystemComponent* InventorySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInteractionSystemComponent* InteractionSystemComponent = nullptr;

};