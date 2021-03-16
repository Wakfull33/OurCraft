// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GravityActorComponent.h"
#include "GravitySetterComponent.h"
#include "PlanetaryMovementComponent.h"
#include "../Generation/PlanetActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "InventorySystemComponent.h"
#include "InteractionSystemComponent.h"


AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPlanetaryMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//Adding Gravity Actor Component
	//GravityActorComponent = CreateDefaultSubobject<UGravityActorComponent>(TEXT("Gravity Actor"));

	InventorySystemComponent = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("Inventory System"));
	InteractionSystemComponent = CreateDefaultSubobject<UInteractionSystemComponent>(TEXT("Interaction System"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Forward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::LookUp);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMainCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMainCharacter::TouchStopped);

}

UPlanetaryMovementComponent* AMainCharacter::GetPlanetaryMovementComponent() const
{
	return Cast<UPlanetaryMovementComponent>(GetMovementComponent());
}

void AMainCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMainCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector Gravity(FVector::ZeroVector);


	if (GravitySetterComponent != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("[o] GravityComponent:  Owner: %s    GravityType: %s"), *GravitySetterComponent->GetOwner()->GetName(), *UEnum::GetValueAsString<EGravityType>(GravitySetterComponent->GravityType.GetValue()))

		switch (GravitySetterComponent->GravityType) {
			case GT_SPHERE: {
				Gravity = (GravitySetterComponent->GetOwner()->GetActorLocation() - GetActorLocation()).GetSafeNormal();
				break;
			}
			case GT_PLANET: {
				Gravity = ((Cast<APlanetActor>(GravitySetterComponent->GetOwner()))->PlanetCenter - GetActorLocation()).GetSafeNormal();
				DrawDebugPoint(GetWorld(), (Cast<APlanetActor>(GravitySetterComponent->GetOwner()))->PlanetCenter, 100.f, FColor::Red);
				break;
			}
			case GT_TILE: {
				Gravity = (-GravitySetterComponent->GetOwner()->GetActorUpVector().GetSafeNormal());
				break;
			}
		}

		GetPlanetaryMovementComponent()->SetGravityDirection(UKismetMathLibrary::VInterpTo(GetPlanetaryMovementComponent()->GetGravityDirection(false), Gravity, DeltaSeconds, 5.0f));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GravitySetterComponent not found !"))
	}

	//Handle Camera orientation
	// CameraBoom->AddRelativeRotation(FRotator(GetInputAxisValue("LookUp") * -1, 0.0f, 0.0f));
	// AddActorLocalRotation(FRotator(0.0f, GetInputAxisValue("Turn"), 0.0f));

}

void AMainCharacter::SetupGravity(UGravitySetterComponent* GravitySetter)
{
	GravitySetterComponent = GravitySetter;
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FRotator YawRotation(GetActorRotation().Pitch, Rotation.Yaw, GetActorRotation().Roll);
		
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		//AddMovementInput(GetActorForwardVector(), Value);

		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + (100 * Direction), 10, FColor::Green, false, 30);
		// UEngine().AddOnScreenDebugMessage(0, 1, FColor::Blue, FString::Printf(TEXT("Length: %f"), Direction.Size()));
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement in that direction
		//AddMovementInput(Direction, Value);
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMainCharacter::Turn(float Value)
{
	if((Controller != NULL) && (Value != 0.0f))
	{
		AddControllerYawInput(Value);
	}
}

void AMainCharacter::LookUp(float Value)
{
	if((Controller != NULL) && (Value != 0.0f))
	{
		AddControllerPitchInput(Value);
	}
}
