// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../MyGameInstance.h"
#include "../../../Managers/MyUIManager.h"
#include "PlayerHitIndicator.h"
#include "PlayerHitUI.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESISTERS_API UPlayerHitUI : public UUserWidget
{
	GENERATED_BODY()

	//Public variables here.
	UPlayerHitUI(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Not the best way due to time constraints
public:

	//Our base material that will be the template for our material instance
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface * MainMaterial = nullptr;

	//Texture we'll set as a parameter to our dynamic material instance
	UPROPERTY(EditDefaultsOnly)
		class UTexture * MainTexture = nullptr;

	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * HitImageOne = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * HitImageTwo = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * HitImageThree = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * HitImageFour = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * HitImageFive = nullptr;

	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * BackgroundOne = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * BackgroundTwo = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * BackgroundThree = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * BackgroundFour = nullptr;
	//Generate some things so we can spawn them or something
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * BackgroundFive = nullptr;

	TArray<FPlayerHitIndicator> hitArray;
	TArray<UImage* > imageArray;
	TArray<UImage*> spriteArray;


};

