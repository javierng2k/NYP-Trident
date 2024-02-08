// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSkillGauge.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"


FWeaponSkillGauge::FWeaponSkillGauge()
{
}

void FWeaponSkillGauge::ApplyToImage(UImage * imageToApply)
{
	imageToApply->SetBrushFromMaterial(MaterialInstance);
}

void FWeaponSkillGauge::ApplyToMaterial()
{

	MaterialInstance->SetScalarParameterValue("Use Texture", weaponSkillParameters.useTexture);
	MaterialInstance->SetScalarParameterValue("Percentage", weaponSkillParameters.percent);
	MaterialInstance->SetVectorParameterValue("Color", Color);

	if(weaponSkillParameters.useTexture)
		MaterialInstance->SetTextureParameterValue("Texture", Texture);
}

void FWeaponSkillGauge::UpdatePercent()
{
	MaterialInstance->SetScalarParameterValue("Percentage", weaponSkillParameters.percent);
}
