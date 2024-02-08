// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CircularHealthParameters.generated.h"

/**
 * 
 */
 /**
  *
  */
  /**
   *This struct makes it easier to instantiate a healthbar, such that all the parameters are already here.
   * Initialize more of these if you have more healthbars.
   */
USTRUCT(BlueprintType)
struct FCircularHealthParameters
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool useTwoWaves;
	//The fill percentage of the image (0.5 being half)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float fillPercentage;
	//The speed in which the back wave moves
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float backWaveSpeed;
	//The texture scale for the back wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float backWaveTextureScale;
	//The deltaTime scale multplier for the back wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float backWaveTextureTimeScale;
	//The speed in which the front wave moves
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float frontWaveSpeed;
	//The texture scale for the front wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float frontWaveTextureScale;
	//The deltaTime scale multplier for the front wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float frontWaveTextureTimeScale;
	//The speed in which the texture moves for the front wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector2D frontWavePanSpeed;
	//The speed in which the texture moves for the back wave
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector2D backWavePanSpeed;
	//UTiling
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float uTiling;
	//VTiling
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float vTiling;
	//UV range in terms of 0 and 1 for the front wave
	float frontWaveOffset;
	//UV range in terms of 0 and 1 for the back wave
	float backWaveOffset;

	FCircularHealthParameters();

};

