// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DashGaugeParameters.generated.h"

/**
 * 
 */
 /**
  * This struct holds all the parameters that the gauge has
  * I have made this accessible from the editor so change it from there.
  */
USTRUCT(BlueprintType)
struct FDashGaugeParameters
{
	GENERATED_BODY()

		//The progress of the image in the range of 0 to 1.
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float percent;
	//The brightness of the image;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float brightness;
	//How thick you want the circle to be
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float desiredRadius;
	//The distance offset from the center(0.5,0.5) to start drawing the circle
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float initialRadius;
	//The speed in coordinates to move the texture
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector2D panSpeeds;
	//How big the texture mapped on the circle.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float textureScale;
	//This is the deltaTime of the entire texture moving.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float textureTimeScale;
	FDashGaugeParameters();


};

