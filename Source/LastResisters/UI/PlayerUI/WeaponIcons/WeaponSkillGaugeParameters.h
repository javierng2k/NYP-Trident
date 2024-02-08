// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponSkillGaugeParameters.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponSkillGaugeParameters
{
	GENERATED_BODY()		
		
		//The progress of the image in the range of 0 to 1.
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool useTexture;

		//The progress of the image in the range of 0 to 1.
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float percent;


};
