// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "CircularHealthParameters.h"
#include "CircularHealth.generated.h"

USTRUCT(BlueprintType)
struct FCircularHealth
{
	GENERATED_BODY()

		//Our base material that will be the template for our material instance
		UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface * Material = nullptr;

	//Our actual materialInstance 
	class UMaterialInstanceDynamic * MaterialInstance = nullptr;

	//Texture we'll set as a parameter to our dynamic material instance
	UPROPERTY(EditDefaultsOnly)
		class UTexture * FrontWaveTexture = nullptr;

	UPROPERTY(EditDefaultsOnly)
		class UTexture * BackWaveTexture = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FCircularHealthParameters circularHealthParameters;

	//Constructor for the struct
	FCircularHealth();

	//Applies the material to target image
	void ApplyToImage(UImage * imageToApply);

	//Applies the current values stored inside the parameters to the material
	void ApplyToMaterial();

	//Update the fill percentage of the circular health
	void UpdatePercent();

	//Update the waves
	void UpdateOffset(float inDeltaTime);

	//Modulus function
	float FindModulus(float a, float b);



};
