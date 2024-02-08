// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerHitUIParameters.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FPlayerHitUIParameters
{
	GENERATED_BODY()

	FFloat16 duration;
	FVector position;
	FFloat16 rotation;
	FString enemyID;

	//The boolean that changes wheneve rhte value change so the rate is only calculated once
	bool calculateRate;
	//The float that stores the rate
	float rate;
	//The delay timer that counts towards the delay
	float delayTimer;
	//The delay
	float delay;

	//Current fill which is range from 0 to 1
	float currentFill;
	//Desired fill from range 0 to 1
	float desiredFill;

	bool useTexture;
	float textureBrightness;

	FPlayerHitUIParameters();


};
