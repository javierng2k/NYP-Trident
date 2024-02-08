// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyUI.h"
#include "../../SpriteAnimation/SpriteAnimation.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../../Math/UIMath.h"
#include "Components/Image.h"

UEnemyUI::UEnemyUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UEnemyUI::NativeConstruct()
{	
	// Do some custom setup
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	//Create the delayedGauge materialInstance and apply it to the actual Image
	delayedArmorGauge.MaterialInstance = UMaterialInstanceDynamic::Create(delayedArmorGauge.Material, this);
	delayedArmorGauge.ApplyToMaterial();
	delayedArmorGauge.ApplyToImage(D_ArmorGauge);

	//Create the delayedGauge materialInstance and apply it to the actual Image
	delayedHealthGauge.MaterialInstance = UMaterialInstanceDynamic::Create(delayedHealthGauge.Material, this);
	delayedHealthGauge.ApplyToMaterial();
	delayedHealthGauge.ApplyToImage(D_HPGauge);

	//Create the delayedGauge materialInstance and apply it to the actual Image
	instantArmorGauge.MaterialInstance = UMaterialInstanceDynamic::Create(instantArmorGauge.Material, this);
	instantArmorGauge.ApplyToMaterial();
	instantArmorGauge.ApplyToImage(I_ArmorGauge);

	//Create the delayedGauge materialInstance and apply it to the actual Image
	instantHealthGauge.MaterialInstance = UMaterialInstanceDynamic::Create(instantHealthGauge.Material, this);
	instantHealthGauge.ApplyToMaterial();
	instantHealthGauge.ApplyToImage(I_HPGauge);

	//Set the delay.
	healthDelayTimer = healthDelay;
	armorDelayTimer = armorDelay;

	UE_LOG(LogTemp, Warning, TEXT("Size: %d"), crackDeviations.Num());
}

void UEnemyUI::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);
	// Do your custom tick stuff here

#pragma region Normalization
		//Call the normalizedFunctions
	NormalizeArmorValue();
	NormalizeHealthValue();
#pragma endregion

#pragma region HealthGauge
	if (calculateDifferenceHealth)
	{
		healthDelayTimer = healthDelay;
		UpdateHealthGauge(InDeltaTime);
	}
	else
	{
		if (healthDelayTimer > 0)
			healthDelayTimer -= InDeltaTime;
		else
			UpdateHealthGauge(InDeltaTime);
	}
#pragma endregion

#pragma region ArmorGauge
	if (calculateDifferenceArmor)
	{
		armorDelayTimer = armorDelay;
		UpdateArmorGauge(InDeltaTime);
	}
	else
	{
		if (armorDelayTimer > 0)
			armorDelayTimer -= InDeltaTime;
		else
			UpdateArmorGauge(InDeltaTime);
	}
#pragma endregion

	healthAmount -= 0.15f;

	 GetCrackEdges();

}

void UEnemyUI::UpdateHealthGauge(float inDeltaTime)
{
	if (calculateDifferenceHealth)
	{
		healthRate = (f_desiredHealth - f_currentHealth) / healthDownTime;
		calculateDifferenceHealth = false;
	}

	//Else we just keep minusing

	//Only if they're not the same then we bother to do these

	if (f_desiredHealth != f_currentHealth)
	{
		f_currentHealth += (healthRate * inDeltaTime);

		if (healthRate > 0)
		{
			if (f_currentHealth >= f_desiredHealth)
				f_currentHealth = f_desiredHealth;
		}
		else
		{
			if (f_currentHealth <= f_desiredHealth)
				f_currentHealth = f_desiredHealth;
		}

		instantHealthGauge.healthParameters.percentage = f_desiredHealth;
		delayedHealthGauge.healthParameters.percentage = f_currentHealth;

		//Update the percentages
		instantHealthGauge.UpdatePercent();
		delayedHealthGauge.UpdatePercent();
	}
	else
	{
		//End function
	}
}

void UEnemyUI::UpdateArmorGauge(float inDeltaTime)
{
	if (calculateDifferenceArmor)
	{
		armorRate = (f_desiredArmor - f_currentArmor) / armorDownTime;
		calculateDifferenceArmor = false;
	}

	//Else we just keep minusing

	//Only if they're not the same then we bother to do these

	if (f_desiredArmor != f_currentArmor)
	{
		f_currentArmor += (armorRate * inDeltaTime);

		if (healthRate > 0)
		{
			if (f_currentArmor >= f_desiredArmor)
				f_currentArmor = f_desiredArmor;
		}
		else
		{
			if (f_currentArmor <= f_desiredArmor)
				f_currentArmor = f_desiredArmor;
		}

		instantArmorGauge.armorParameters.percentage = f_desiredArmor;
		delayedArmorGauge.armorParameters.percentage = f_currentArmor;

		//Update the percentages
		instantArmorGauge.UpdatePercent();
		delayedArmorGauge.UpdatePercent();
	}
	else
	{
		//End function
	}
}

void UEnemyUI::NormalizeHealthValue()
{
	f_desiredHealth = UIMath::NormalizeValueCustomRange(UIMath::NormalizeValue((float)healthAmount, minHealth, maxHealth), 0.04f, 0.97f);
}

void UEnemyUI::NormalizeArmorValue()
{
	f_desiredArmor = UIMath::NormalizeValueCustomRange(UIMath::NormalizeValue((float)armorAmount, minHealth, maxHealth), 0.04f, 0.97f);
}

void UEnemyUI::GetCrackEdges()
{
	for (auto deviations : crackDeviations)
	{
		UE_LOG(LogTemp, Warning, TEXT("Deviation Amount: %f, Health Amount: %f"), deviations.amount, healthAmount);
		if (healthAmount > deviations.amount)
			continue;

		currentEdge.amount = deviations.amount;
		currentEdge.ImageForDisplay = deviations.ImageForDisplay;
		CrackedImage->SetBrushFromTexture(currentEdge.ImageForDisplay);

		UE_LOG(LogTemp, Warning, TEXT("Current Edge amount %f"), currentEdge.amount);
		
		break;
	}

}
