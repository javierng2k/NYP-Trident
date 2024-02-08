// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../ArmorGauge/EnemyArmorGauge.h"
#include "../HealthGauge/EnemyHealthGauge.h"
#include "../CrackEdges/CrackedEdge.h"
#include "EnemyUI.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESISTERS_API UEnemyUI : public UUserWidget
{
	GENERATED_BODY()
public:
	//Public variables here.
	UEnemyUI(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Get the images for the gauges
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * D_HPGauge = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * I_HPGauge = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * D_ArmorGauge = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * I_ArmorGauge = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * CrackedImage = nullptr;

	//Struct that holds the values of the delayed HP gauge
	UPROPERTY(EditDefaultsOnly)
	FEnemyHealthGauge delayedHealthGauge;
	//Struct that holds the values of the delayed Armor gauge
	UPROPERTY(EditDefaultsOnly)
	FEnemyHealthGauge instantHealthGauge;
	//Struct that holds the values of the instant HP gauge
	UPROPERTY(EditDefaultsOnly)
	FEnemyArmorGauge delayedArmorGauge;
	//Struct that holds the values of the instant Armor gauge
	UPROPERTY(EditDefaultsOnly)
	FEnemyArmorGauge instantArmorGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
		float minHealth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
		float maxHealth = 100;

	//Array of the cracked edges to check if it works
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crack Deviations")
	TArray<FCrackedEdge> crackDeviations;

	FCrackedEdge currentEdge;

#pragma region HealthGaugeParameters
	//Amount of health now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Gauge Parameters")
		float healthAmount = 50;
	//Time it takes for the delayed gauge to catch up to the instant gauge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Gauge Parameters")
		float healthDownTime = 0.5f;
	//Time before the delayed gauge tries to catch up to the instant gauge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Gauge Parameters")
		float healthDelay = 0.5;

	//Current and desired values in values of 0 to 1
	float f_currentHealth = 1;
	float f_desiredHealth = 1;

	//The boolean that changes whenever the value changes so the rate is only calculated once
	bool calculateDifferenceHealth = true;
	//The float that stores the rate
	float healthRate = 0;
	//The delay timer that counts towards the delay
	float healthDelayTimer;
#pragma endregion

#pragma region ArmorGaugeParameters
	//Amount of health now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Gauge Parameters")
		float armorAmount = 50;
	//Time it takes for the delayed gauge to catch up to the instant gauge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Gauge Parameters")
		float armorDownTime = 0.5f;
	//Time before the delayed gauge tries to catch up to the instant gauge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Gauge Parameters")
		float armorDelay = 0.5;

	//Current and desired values in values of 0 to 1
	float f_currentArmor = 1;
	float f_desiredArmor = 1;

	//The boolean that changes whenever the value changes so the rate is only calculated once
	bool calculateDifferenceArmor = true;
	//The float that stores the rate
	float armorRate = 0;
	//The delay timer that counts towards the delay
	float armorDelayTimer;
#pragma endregion

#pragma region Functions
	//Update the health gauge
	void UpdateHealthGauge(float inDeltaTime);
	//Update the armor gauge
	void UpdateArmorGauge(float inDeltaTime);
	//To normalize the input from and clamp...(not a normalize function)
	void NormalizeHealthValue();
	//To normalize the input from and clamp...(not a normalize function)
	void NormalizeArmorValue();

	//Check which image to display
	void GetCrackEdges();
	
#pragma endregion

};
