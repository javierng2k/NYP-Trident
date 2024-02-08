// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitUIParameters.h"

FPlayerHitUIParameters::FPlayerHitUIParameters()
	: duration(0)
	, position(FVector(0.f, 0.f, 0.f))
	, rotation(0)
	, enemyID("monkaS")
	, calculateRate(true)
	, rate(0)
	, delayTimer(0)
	, delay(0)
	,desiredFill(1)
	,currentFill(0)
	,useTexture(true)
	,textureBrightness(1.0f)
{
}
