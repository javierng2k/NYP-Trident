// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CrackedEdge.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCrackedEdge
{
	GENERATED_BODY()

	FCrackedEdge();
	FCrackedEdge(FCrackedEdge & other);

	UPROPERTY(EditDefaultsOnly)
	//Amount before this is activated
	float amount;
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D * ImageForDisplay;

};
