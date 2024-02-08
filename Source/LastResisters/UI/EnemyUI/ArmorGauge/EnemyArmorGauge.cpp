// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyArmorGauge.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

FEnemyArmorGauge::FEnemyArmorGauge()
{
}

void FEnemyArmorGauge::ApplyToImage(UImage * imageToApply)
{
	imageToApply->SetBrushFromMaterial(MaterialInstance);
}

void FEnemyArmorGauge::ApplyToMaterial()
{
	MaterialInstance->SetTextureParameterValue("Opacity Mask", OpacityMask);
	MaterialInstance->SetTextureParameterValue("Texture", Texture);
	MaterialInstance->SetScalarParameterValue("Brightness", armorParameters.brightness);
	MaterialInstance->SetScalarParameterValue("Percentage", armorParameters.percentage);
	MaterialInstance->SetScalarParameterValue("Use Texture", armorParameters.useTexture);

	if (armorParameters.useTexture == false)
		MaterialInstance->SetVectorParameterValue("Color", armorParameters.gaugeColor);
}

void FEnemyArmorGauge::UpdatePercent()
{
	MaterialInstance->SetScalarParameterValue("Percentage", armorParameters.percentage);
}
