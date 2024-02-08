// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerHitUIParameters.h"
#include "../../../Managers/MyAttackManager.h"
#include "Materials/MaterialInterface.h"
#include "PlayerHitIndicator.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerHitIndicator
{
	GENERATED_BODY()

		//The linked image
		class UImage * LinkedImage;
	class UImage * LinkedBackground;
		

		class UTexture * MainTexture = nullptr;

	//Our actual materialInstance 
		class UMaterialInstanceDynamic * MaterialInstance = nullptr;


	UPROPERTY(EditDefaultsOnly)
		FPlayerHitUIParameters playerHitParameters;

	FPlayerHitIndicator();
	FPlayerHitIndicator(bool isDefault);

	//No pointer work around
	bool isDefault;

	void ApplyToImage(UImage * imageToApply);
	void UpdatePercent();
	void ApplyToMaterial();
	void AssignParametersFromInfo(MyAttackManager::Attack_Info infoReceived);
	void PrintDetails();
	void UpdateFillAmount(float inDeltaTime);

};
