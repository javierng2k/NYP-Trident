// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "EnemyHealthGaugeParameters.h"
#include "EnemyHealthGauge.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyHealthGauge
{
	GENERATED_BODY()

	//Our base material that will be the template for our material instance
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface * Material = nullptr;

	//Our actual materialInstance 
		class UMaterialInstanceDynamic * MaterialInstance = nullptr;

	//Texture we'll set as a parameter to our dynamic material instance
	UPROPERTY(EditDefaultsOnly)
		class UTexture * OpacityMask = nullptr;

	UPROPERTY(EditDefaultsOnly)
		class UTexture * Texture = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FEnemyHealthGaugeParameters healthParameters;

	FEnemyHealthGauge();

	void ApplyToImage(UImage * imageToApply);
	void ApplyToMaterial();
	void UpdatePercent();
	
};
