// Fill out your copyright notice in the Description page of Project Settings.


#include "CircularHealthParameters.h"

FCircularHealthParameters::FCircularHealthParameters()
	: useTwoWaves(true)
	, fillPercentage(0.5f)
	, backWaveSpeed(2.5f)
	, backWaveTextureScale(1.0f)
	, backWaveTextureTimeScale(1.0f)
	, frontWaveSpeed()
	, frontWaveTextureScale(1.f)
	, frontWaveTextureTimeScale(1.f)
	, frontWavePanSpeed(0.f, 0.f)
	, backWavePanSpeed(0.f, 0.f)
	, uTiling(1.f)
	, vTiling(8.f)
	, frontWaveOffset(0.f)
	, backWaveOffset(0.f)
{

}
