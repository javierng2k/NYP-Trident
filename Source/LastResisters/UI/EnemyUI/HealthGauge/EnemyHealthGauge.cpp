// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthGauge.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

FEnemyHealthGauge::FEnemyHealthGauge()
{
}

void FEnemyHealthGauge::ApplyToImage(UImage * imageToApply)
{
	imageToApply->SetBrushFromMaterial(MaterialInstance);
}

void FEnemyHealthGauge::ApplyToMaterial()
{
	MaterialInstance->SetTextureParameterValue("Opacity Mask", OpacityMask);
	MaterialInstance->SetTextureParameterValue("Texture", Texture);
	MaterialInstance->SetScalarParameterValue("Brightness", healthParameters.brightness);
	MaterialInstance->SetScalarParameterValue("Percentage", healthParameters.percentage);
	MaterialInstance->SetScalarParameterValue("Use Texture", healthParameters.useTexture);

	if(healthParameters.useTexture == false)
		MaterialInstance->SetVectorParameterValue("Color", healthParameters.gaugeColor);
}

void FEnemyHealthGauge::UpdatePercent()
{
	MaterialInstance->SetScalarParameterValue("Percentage", healthParameters.percentage);
}
