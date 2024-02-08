// Fill out your copyright notice in the Description page of Project Settings.


#include "CircularHealth.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

FCircularHealth::FCircularHealth()
{
	
}

void FCircularHealth::ApplyToImage(UImage * imageToApply)
{
	imageToApply->SetBrushFromMaterial(MaterialInstance);
}
void FCircularHealth::ApplyToMaterial()
{
	MaterialInstance->SetScalarParameterValue("UseTwoWaves", circularHealthParameters.useTwoWaves);
	//Apply to material
	MaterialInstance->SetScalarParameterValue("FillPercentage", circularHealthParameters.fillPercentage);
	MaterialInstance->SetScalarParameterValue("BackWaveSpeed", circularHealthParameters.backWaveSpeed);
	MaterialInstance->SetScalarParameterValue("BackWaveTextureScale", circularHealthParameters.backWaveTextureScale);
	MaterialInstance->SetScalarParameterValue("BackWaveTextureTimeScale", circularHealthParameters.backWaveTextureTimeScale);
	MaterialInstance->SetScalarParameterValue("T_BackWavePanSpeedX", circularHealthParameters.backWavePanSpeed.X);
	MaterialInstance->SetScalarParameterValue("T_BackWavePanSpeedY", circularHealthParameters.backWavePanSpeed.Y);
	MaterialInstance->SetScalarParameterValue("UTiling", circularHealthParameters.uTiling);
	MaterialInstance->SetScalarParameterValue("VTiling", circularHealthParameters.vTiling);
	MaterialInstance->SetTextureParameterValue("BackWaveTexture", BackWaveTexture);

	MaterialInstance->SetTextureParameterValue("FrontWaveTexture", FrontWaveTexture);
	MaterialInstance->SetScalarParameterValue("FrontWaveSpeed", circularHealthParameters.frontWaveSpeed);
	MaterialInstance->SetScalarParameterValue("FrontWaveTextureScale", circularHealthParameters.frontWaveTextureScale);
	MaterialInstance->SetScalarParameterValue("FrontWaveTextureTimeScale", circularHealthParameters.frontWaveTextureTimeScale);
	MaterialInstance->SetScalarParameterValue("T_FrontWavePanSpeedX", circularHealthParameters.frontWavePanSpeed.X);
	MaterialInstance->SetScalarParameterValue("T_FrontWavePanSpeedY", circularHealthParameters.frontWavePanSpeed.Y);

}
void FCircularHealth::UpdatePercent()
{
	MaterialInstance->SetScalarParameterValue("FillPercentage", circularHealthParameters.fillPercentage);
}

void FCircularHealth::UpdateOffset(float inDeltaTime)
{
	circularHealthParameters.backWaveOffset = FindModulus(((circularHealthParameters.backWaveSpeed * inDeltaTime) + circularHealthParameters.backWaveOffset), 1);
	//UE_LOG(LogTemp, Warning, TEXT("Back Offset: %f, Back Speed: %f"), circularHealthParameters.backWaveOffset, circularHealthParameters.backWaveSpeed);
	MaterialInstance->SetScalarParameterValue("BackWaveOffset", circularHealthParameters.backWaveOffset);

	if (circularHealthParameters.useTwoWaves)
	{
		circularHealthParameters.frontWaveOffset = FindModulus(((circularHealthParameters.frontWaveSpeed * inDeltaTime) + circularHealthParameters.frontWaveOffset), 1);
		//UE_LOG(LogTemp, Warning, TEXT("Front Offset: %f, Front Speed: %f"), circularHealthParameters.frontWaveOffset, circularHealthParameters.frontWaveSpeed);
		MaterialInstance->SetScalarParameterValue("FrontWaveOffset", circularHealthParameters.frontWaveOffset);
	}
}

float FCircularHealth::FindModulus(float a, float b)
{
	float mod;
	if (a < 0.f)
		mod = -a;
	else
		mod = a;

	if (b < 0.f)
		b = -b;

	//Find mod by repeated subtraction
	while (mod >= b)
		mod = mod - b;

	//Sign of result typicall depends on sign of a
	if (a < 0)
		return -mod;

	return mod;
}

