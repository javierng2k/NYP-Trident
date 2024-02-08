// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyHealthGaugeParameters.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyHealthGaugeParameters
{
	GENERATED_BODY()

	//Implement all shader variables here

		//Constructor
	FEnemyHealthGaugeParameters();

	//The brightness multiplier of the texture
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float brightness;
	//The progress of the image in the range of 0 to 1.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float percentage;
	//Do we want to use a texture?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool useTexture;
	//The color of the progres if no texture is used.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FColor gaugeColor;

};
