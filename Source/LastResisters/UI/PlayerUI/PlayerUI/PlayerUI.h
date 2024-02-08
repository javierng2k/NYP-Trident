// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../CircularHealth/CircularHealth.h"
#include "../DashGauge/DashGauge.h"
#include "../WeaponIcons/WeaponSkillGauge.h"
#include "PlayerUI.generated.h"


/**
 * The class for handling the player's UI. (not very well written as u can see)
 */
UCLASS()
class LASTRESISTERS_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	//Public variables here.
	UPlayerUI(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Objects start here.
	//The image for the delayed dash gauge
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * DelayedDashGauge = nullptr;
	//Image for the instant dash gauge
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * InstantDashGauge = nullptr;
	//Image for the circular health
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * CircularHealth = nullptr;
	//Textblock for health
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock * HealthText = nullptr;
	//Image for the main weapon gauge
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * MainGauge = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * SubGauge = nullptr;

	//Image for the main weapon gauge charge effect
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * MainChargeEffect = nullptr;
	//Image for the main weapon gauge flame effect
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * MainFlameEffect = nullptr;

	//Image for the main weapon gauge charge effect
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * SubChargeEffect = nullptr;
	//Image for the main weapon gauge flame effect
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage * SubFlameEffect = nullptr;

	//Struct that holds values of the delayed gauge
	UPROPERTY(EditDefaultsOnly)
		FDashGauge delayedGauge;
	//Struct that holds values of the instant gauge
	UPROPERTY(EditDefaultsOnly)
		FDashGauge instantGauge;
	//Struct that holds values of the circular health
	UPROPERTY(EditDefaultsOnly)
		FCircularHealth f_circularHealth;
	//Struct that holds value for the main weapon gauge
	UPROPERTY(EditDefaultsOnly)
		FWeaponSkillGauge mainWeaponGauge;
	//Struct that holds value for the sub weapon gauge
	UPROPERTY(EditDefaultsOnly)
		FWeaponSkillGauge subWeaponGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float minHealth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float maxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float minDash = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float maxDash = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float minMainWeaponSkill = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float maxMainWeaponSkill = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float minSubWeaponSkill = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
		float maxSubWeaponSkill = 100;

#pragma region DashGaugeParameters

	//Amount of dash now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Gauge Parameters")
		int dashAmount = 1;
	//Time it takes for the delayed gauge to catch up to the instant gauge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Gauge Parameters")
		float timeToDeduct = 0.5f;
	//Time before the delayed gauge tries to catch up to the instant gauge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Gauge Parameters")
		float delay = 0.5;

	//Current and desired values in values of 0 to 1
	float f_currentDash = 1;
	float f_desiredDash = 1;

	//The boolean that changes whenever the value changes so the rate is only calculated once
	bool calculateDifference = true;
	//The float that stores the rate
	float rate = 0;
	//The delay timer that counts towards the delay
	float delayTimer;

#pragma endregion

#pragma region CircularHealthParameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		int m_actualHealth = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float lerpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float epsilon;

	float f_currentHealth = 1;
	float f_desiredHealth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float desiredSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float healthLerpSpeed;

	//For going down.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float healthDownTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float healthDownDelay = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Parameters")
		float healthEpsilon;

	//Health Hit Variables
	float initialSpeed;
	float currentSpeed;

	float healthDownRate;
	bool calculateHit = true;
	bool direction = true;
	float timer = 0;
	
	void DoHit();

#pragma endregion

#pragma region MainGaugeParameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Gauge Parameters")
		float mainWeaponSkillGauge = 30;

	float f_mainWeaponSkillGauge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Gauge Parameters")
		float  subWeaponSkillGauge = 30;
	
	float f_subWeaponSkillGauge = 1;

#pragma endregion

#pragma region Functions
	//Update the skill gauge
	void UpdateDashGauge(float inDeltaTime);

	//Update the healthbar
	void UpdateHealthbar(float inDeltaTime);

	//Update weapon bars
	void UpdateMainWeaponSkillGauge(float inDeltaTime);

	//Update sub weapon bar
	void UpdateSubWeaponSkillGauge(float inDeltaTime);


	//To normalize the input from and clamp...(not a normalize function)
	void NormalizeHealthValue();
	//To normalize the input from and clamp...(not a normalize function)
	void NormalizeDashGauge();
	//To normalize the input from and clamp...(not a normalize function)
	void NormalizeWeaponGauges();

	void Hit(float inDeltaTime);
#pragma endregion

protected:
	//Protected variables here
private:
	//Private variables here

};