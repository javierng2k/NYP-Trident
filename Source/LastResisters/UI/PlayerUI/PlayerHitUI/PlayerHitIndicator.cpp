// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitIndicator.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"

FPlayerHitIndicator::FPlayerHitIndicator()
	: isDefault(false)
{
}

FPlayerHitIndicator::FPlayerHitIndicator(bool isDefault_)
	: isDefault(isDefault_)
{

}

void FPlayerHitIndicator::ApplyToImage(UImage * imageToApply)
{
	imageToApply->SetBrushFromMaterial(MaterialInstance);
}

void FPlayerHitIndicator::UpdatePercent()
{
	//This is the time thingy?
	MaterialInstance->SetScalarParameterValue("Percentage", playerHitParameters.currentFill);
}

void FPlayerHitIndicator::ApplyToMaterial()
{

		MaterialInstance->SetTextureParameterValue("Texture", MainTexture);
		MaterialInstance->SetScalarParameterValue("Percentage", playerHitParameters.currentFill);
		MaterialInstance->SetScalarParameterValue("TextureBrightness", playerHitParameters.textureBrightness);
		MaterialInstance->SetScalarParameterValue("Use Texture", playerHitParameters.useTexture);

	
}

void FPlayerHitIndicator::AssignParametersFromInfo(MyAttackManager::Attack_Info infoReceived)
{
	//Call default and change the rest
	playerHitParameters = FPlayerHitUIParameters();
	playerHitParameters.enemyID = infoReceived.info_EnemyID;
	playerHitParameters.position = infoReceived.info_Position;
	playerHitParameters.rotation = infoReceived.info_Rotation;
	playerHitParameters.duration = infoReceived.info_CountdownTimer;
	playerHitParameters.calculateRate = true;

}


void FPlayerHitIndicator::PrintDetails()
{
	UE_LOG(LogTemp, Warning, TEXT("Name: %s , Position : (%f, %f, %f), Rotation : (%f), Duration : (%f)")
		, *playerHitParameters.enemyID
		, playerHitParameters.position.X
		, playerHitParameters.position.Y
		, playerHitParameters.position.Z
		, (float)playerHitParameters.rotation
		, (float)playerHitParameters.duration);
}

void FPlayerHitIndicator::UpdateFillAmount(float inDeltaTime)
{
	if (playerHitParameters.calculateRate)
	{

		playerHitParameters.rate = (playerHitParameters.desiredFill - playerHitParameters.currentFill) / playerHitParameters.duration;
		playerHitParameters.calculateRate = false;
		//UE_LOG(LogTemp, Warning, TEXT("Calculated rate : %f"), playerHitParameters.rate);
	}
	//Else we keep minusing and only if they;re not already the same

	if (playerHitParameters.desiredFill != playerHitParameters.currentFill)
	{
		playerHitParameters.currentFill += (playerHitParameters.rate)* inDeltaTime;

		if (playerHitParameters.rate > 0)
		{
			if (playerHitParameters.currentFill >= playerHitParameters.desiredFill)
				playerHitParameters.currentFill = playerHitParameters.desiredFill;
		}
		else
		{
			if (playerHitParameters.currentFill <= playerHitParameters.desiredFill)
				playerHitParameters.currentFill = playerHitParameters.desiredFill;
		}

		//Update percent
		UpdatePercent();
	}
	else
	{
		//Function ended...
		//Set the brush to cant see but sure.
		if(LinkedImage != nullptr)
			LinkedImage->SetVisibility(ESlateVisibility::Hidden);
		if (LinkedBackground != nullptr)
			LinkedBackground->SetVisibility(ESlateVisibility::Hidden);

		//aslo set duration to 0? or something, temporary codes
		playerHitParameters.duration = 0;
	}
}


