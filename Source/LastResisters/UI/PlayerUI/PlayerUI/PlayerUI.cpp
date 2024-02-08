// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../Math/UIMath.h"
#include "../../SpriteAnimation/SpriteAnimation.h"

UPlayerUI::UPlayerUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UPlayerUI::NativeConstruct()
{
	// Do some custom setup

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	//Create the delayedGauge materialInstance and apply it to the actual Image
	delayedGauge.MaterialInstance = UMaterialInstanceDynamic::Create(delayedGauge.Material, this);
	delayedGauge.ApplyToMaterial();
	delayedGauge.ApplyToImage(DelayedDashGauge);

	//Create the instant gauge's materialInstance and apply it to the actual Image
	instantGauge.MaterialInstance = UMaterialInstanceDynamic::Create(instantGauge.Material, this);
	instantGauge.ApplyToMaterial();
	instantGauge.ApplyToImage(InstantDashGauge);

	//Create the health bar's materialInstance and apply it to the actual image
	f_circularHealth.MaterialInstance = UMaterialInstanceDynamic::Create(f_circularHealth.Material, this);
	f_circularHealth.ApplyToMaterial();
	f_circularHealth.ApplyToImage(CircularHealth);

	//Create the main weapon's gauge materialInstance and apply it to the actual image
	mainWeaponGauge.MaterialInstance = UMaterialInstanceDynamic::Create(mainWeaponGauge.Material, this);
	mainWeaponGauge.ApplyToMaterial();
	mainWeaponGauge.ApplyToImage(MainGauge);

	//Create the sub weapon's gauge materialInstance and apply it to the actual image
	subWeaponGauge.MaterialInstance = UMaterialInstanceDynamic::Create(subWeaponGauge.Material, this);
	subWeaponGauge.ApplyToMaterial();
	subWeaponGauge.ApplyToImage(SubGauge);

	//Set the delayTimer to be the value of delay at the start.
	delayTimer = delay;

	//Set stuff
	initialSpeed = f_circularHealth.circularHealthParameters.backWaveSpeed;
	currentSpeed = f_circularHealth.circularHealthParameters.backWaveSpeed;

	MainFlameEffect->SetVisibility(ESlateVisibility::Hidden);
	MainChargeEffect->SetVisibility(ESlateVisibility::Hidden);
	SubFlameEffect->SetVisibility(ESlateVisibility::Hidden);
	SubChargeEffect->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerUI::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Do your custom tick stuff here

	//Normalizez and clamp the values for shaders
#pragma region Normalization
	NormalizeHealthValue();
	NormalizeDashGauge();
	NormalizeWeaponGauges();
#pragma endregion

#pragma region Dash Gauges
	if (calculateDifference)
	{
		delayTimer = delay;
		UpdateDashGauge(InDeltaTime);
	}
	else
	{
		if (delayTimer > 0)
			delayTimer -= InDeltaTime;
		else
			UpdateDashGauge(InDeltaTime);
	}

#pragma endregion 

#pragma region Circular Health

	//Update the shader based on the difference between the two healths and lerp.
	UpdateHealthbar(InDeltaTime);

	//To test the hit interaction
	timer += InDeltaTime;
	if (timer > 5)
	{
		DoHit();
		timer = 0;
	}

	//Function that changes wave speed of the healthbar
	Hit(InDeltaTime);

	//Just updating the wavespeed and modulus
	f_circularHealth.UpdateOffset(InDeltaTime);

	//Update the health amount text
	if (HealthText)
		HealthText->SetText(FText::FromString(FString::FromInt(m_actualHealth)));

#pragma endregion

#pragma region Weapon Skill Gauges
	UpdateMainWeaponSkillGauge(InDeltaTime);
	UpdateSubWeaponSkillGauge(InDeltaTime);
#pragma endregion
}

void UPlayerUI::DoHit()
{
	//Reset the variables so the hit function can run again
	calculateHit = true;
	//Set direction to false to increase thespeed of the lerp.
	direction = false;

	//UE_LOG(LogTemp, Warning, TEXT("Do Hit!"));
}

void UPlayerUI::UpdateDashGauge(float inDeltaTime)
{
	if (calculateDifference)
	{
		rate = (f_desiredDash - f_currentDash) / timeToDeduct;
		calculateDifference = false;
	}
	//Else we just keep minusing... and minusing...

	//Only if they're not the same.
	if (f_desiredDash != f_currentDash)
	{
		f_currentDash += (rate * inDeltaTime);

		if (rate > 0)
		{
			if (f_currentDash >= f_desiredDash)
				f_currentDash = f_desiredDash;
		}
		else
		{
			if (f_currentDash <= f_desiredDash)
				f_currentDash = f_desiredDash;
		}

		instantGauge.gaugeParameters.percent = f_desiredDash;
		delayedGauge.gaugeParameters.percent = f_currentDash;

		instantGauge.UpdatePercent();
		delayedGauge.UpdatePercent();
		//Just for testing
		//UE_LOG(LogTemp, Warning, TEXT("Instant Percent: %f, Delayed Percent: %f"), instantGauge.gaugeParameters.percent, delayedGauge.gaugeParameters.percent);
		//UE_LOG(LogTemp, Warning, TEXT("Current: %f, Desired: %f, Rate: %f, Delay: %f"), f_currentSkill, f_desiredSkill, rate, delayTimer);
	}
	else
	{
		calculateDifference = true;
		if (f_desiredDash < 0)
		{
			f_desiredDash = 0.f;
		}
		else if (f_desiredDash == 0.f)
		{
			f_desiredDash = 1.01f;
		}
		else
		{
			//f_desiredDash -= FMath::FRandRange(0.15, 0.2);
		}
	}
}

void UPlayerUI::UpdateHealthbar(float inDeltaTime)
{
	if (f_desiredHealth != f_currentHealth)
	{
		f_currentHealth = FMath::Lerp(f_currentHealth, f_desiredHealth, lerpSpeed * inDeltaTime);
		if (FMath::Abs(f_desiredHealth - f_currentHealth) < epsilon)
			f_currentHealth = f_desiredHealth;

		f_circularHealth.circularHealthParameters.fillPercentage = f_currentHealth;
		f_circularHealth.UpdatePercent();
	}
	else
	{
		//Test the interaction
		//UE_LOG(LogTemp, Warning, TEXT("Health: %d, FillPercentage: %f, Desired: %f, Current: %f"), 
		//	m_actualHealth, 
		//	healthBar.healthbarParameters.fillPercentage,
		//	f_desiredHealth, 
		//	f_currentHealth);
		//m_actualHealth = FMath::FRandRange(0, 100.f);
	}
}

void UPlayerUI::UpdateMainWeaponSkillGauge(float inDeltaTime)
{
	if (mainWeaponSkillGauge < 100)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Main Skill: %d, Main Skill Float: %f"), mainWeaponSkillGauge, f_mainWeaponSkillGauge)
			mainWeaponSkillGauge += 1;
	}
	else if (mainWeaponSkillGauge >= 100)
	{
		USpriteAnimation * mainChargeEffect = Cast<USpriteAnimation>(MainChargeEffect);
		USpriteAnimation * mainFlameEffect = Cast<USpriteAnimation>(MainFlameEffect);
		mainChargeEffect->PlayAnimation();
		mainFlameEffect->PlayAnimation();
	}

	//Set the parameters 
	mainWeaponGauge.weaponSkillParameters.percent = f_mainWeaponSkillGauge;
	mainWeaponGauge.UpdatePercent();
}

void UPlayerUI::UpdateSubWeaponSkillGauge(float inDeltaTime)
{
	if (subWeaponSkillGauge < 100)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Sub Skill: %d, Sub Skill Float: %f"), subWeaponSkillGauge, f_subWeaponSkillGauge)
			subWeaponSkillGauge += 2;
	}
	else if (subWeaponSkillGauge >= 100)
	{
		USpriteAnimation * subChargeEffect = Cast<USpriteAnimation>(SubChargeEffect);
		USpriteAnimation * subFlameEffect = Cast<USpriteAnimation>(SubFlameEffect);
		subChargeEffect->PlayAnimation();
		subFlameEffect->PlayAnimation();
	}

	//Set the parameters 
	subWeaponGauge.weaponSkillParameters.percent = f_subWeaponSkillGauge;
	subWeaponGauge.UpdatePercent();
}

void UPlayerUI::NormalizeHealthValue()
{
	f_desiredHealth = UIMath::NormalizeValueCustomRange(UIMath::NormalizeValue((float)m_actualHealth, minHealth, maxHealth), 0.04f, 0.97f);
}

void UPlayerUI::NormalizeDashGauge()
{
	f_desiredDash = UIMath::NormalizeValueCustomRange(UIMath::NormalizeValue((float)dashAmount, minDash, maxDash), 0.058f, 0.942f);
}

void UPlayerUI::NormalizeWeaponGauges()
{
	f_mainWeaponSkillGauge = UIMath::NormalizeValueCustomRange(UIMath::NormalizeValue((float)mainWeaponSkillGauge, minMainWeaponSkill, maxSubWeaponSkill), 0.058f, 0.942f);
	f_subWeaponSkillGauge = UIMath::NormalizeValueCustomRange(UIMath::NormalizeValue((float)subWeaponSkillGauge, minSubWeaponSkill, maxSubWeaponSkill), 0.058f, 0.942f);
}

void UPlayerUI::Hit(float inDeltaTime)
{
	//If direction is false.
	if (!direction)
	{
		//If the current speed is not the desired
		if (currentSpeed != desiredSpeed)
		{
			//Lerp towards it..
			currentSpeed = FMath::Lerp(currentSpeed,
				desiredSpeed,
				healthLerpSpeed * inDeltaTime);

			//UE_LOG(LogTemp, Warning, TEXT("Lerping to desiredSpeed, Current: %f, Desired: %f , Lerp Time: %f"), currentSpeed, desiredSpeed, healthLerpSpeed * inDeltaTime);

			//If its successful then...
			if (FMath::Abs(desiredSpeed - currentSpeed) <= healthEpsilon)
			{
				currentSpeed = desiredSpeed;
				direction = true;
				//UE_LOG(LogTemp, Warning, TEXT("Lerp complete, changing directions."));
			}
		}
	}
	else
	{
		//Dont do a calculation if the current speed is already equals to the initial.
		if (currentSpeed == initialSpeed)
		{
			//UE_LOG(LogTemp, Warning, TEXT("They are equal."));
			return;
		}

		// the current speed is not equals to the initial
		   //Calculate the healthDownRate once
		if (calculateHit)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Calculated rate"));
			healthDownRate = (initialSpeed - currentSpeed) / healthDownTime;
			calculateHit = false;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Going to initialSpeed, Current: %f, Initial: %f , Rate: %f"), currentSpeed, initialSpeed, healthDownRate);
		currentSpeed += (healthDownRate * inDeltaTime);

		if (healthDownRate > 0)
		{
			if (currentSpeed >= initialSpeed)
				currentSpeed = initialSpeed;
		}
		else
		{
			if (currentSpeed <= initialSpeed)
				currentSpeed = initialSpeed;
		}
	}

	//Update the back wave speed using our current variable
	f_circularHealth.circularHealthParameters.backWaveSpeed = currentSpeed;
}



