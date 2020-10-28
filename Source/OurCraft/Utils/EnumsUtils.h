// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Containers/EnumAsByte.h"
#include "EnumsUtils.generated.h"

/**
 * 
 */
UCLASS()
class OURCRAFT_API UEnumsUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

template<typename TEnum>
static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* enumPtr = FindObject(ANY_PACKAGE, *Name, true);
	if (!enumPtr)
	{
		return FString("Invalid");
	}
	return enumPtr->GetNameByValue((int64)Value).ToString();
}

template <typename EnumType>
static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
{
	UEnum* Enum = FindObject(ANY_PACKAGE, *EnumName, true);
	if (!Enum)
	{
		return EnumType(0);
	}
	return (EnumType)Enum->FindEnumIndex(FName(*String));
}

#pragma region Items Enums

UENUM(BlueprintType)
enum EItemType
{
	IT_ITEM			UMETA(DisplayName = "Item"),
	IT_CONSUMABLE	UMETA(DisplayName = "Consummable"),
	IT_TOOL			UMETA(DisplayName = "Tool"),
	IT_WEAPON		UMETA(DisplayName = "Weapon"),
	IT_ARMOR		UMETA(DisplayName = "Armor"),
	IT_BLOCK		UMETA(DisplayName = "Block")
};

UENUM(BlueprintType)
enum EWeaponType
{
	WT_SWORD	UMETA(DisplayName = "Sword"),
	WT_DAGGER	UMETA(DisplayName = "Dagger"),
	WT_HAMMER	UMETA(DisplayName = "Hammer")
};

UENUM(BlueprintType)
enum EToolType
{
	TT_PICKAXE	UMETA(DisplayName = "Pickaxe"),
	TT_SHOVEL	UMETA(DisplayName = "Shovel"),
	TT_AXE	UMETA(DisplayName = "Axe")
};

UENUM(BlueprintType)
enum EArmorType
{
	AT_HELMET		UMETA(DisplayName = "Helmet"),
	AT_CHESTPLATE	UMETA(DisplayName = "Chestplate"),
	AT_LEGGINGS		UMETA(DisplayName = "Leggings"),
	AT_BOOTS		UMETA(DisplayName = "Boots")
};

#pragma endregion

UENUM(BlueprintType)
enum EGravityType
{
	GT_PLANET		UMETA(DisplayName = "Planet"),
	GT_SPHERE		UMETA(DisplayName = "Sphere"),
	GT_TILE			UMETA(DisplayName = "Tile")
};