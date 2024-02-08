// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitUI.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"

UPlayerHitUI::UPlayerHitUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//UE_LOG(LogTemp, Warning, TEXT("Size: %d"), hitArray.Num());
}

void UPlayerHitUI::NativeConstruct()
{
	// Do some custom setup

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	//Set everything not visible
	imageArray.Add(HitImageOne);
	imageArray.Add(HitImageTwo);
	imageArray.Add(HitImageThree);
	imageArray.Add(HitImageFour);
	imageArray.Add(HitImageFive);

	spriteArray.Add(BackgroundOne);
	spriteArray.Add(BackgroundTwo);
	spriteArray.Add(BackgroundThree);
	spriteArray.Add(BackgroundFour);
	spriteArray.Add(BackgroundFive);

	for (int i = 0; i < imageArray.Num(); i++)
	{
		//Set all to hidden first...
		imageArray[i]->SetVisibility(ESlateVisibility::Hidden);
		spriteArray[i]->SetVisibility(ESlateVisibility::Hidden);
	}

	
	
}

void UPlayerHitUI::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);

	////Give references to the UI manager
	//for (int i = 0; i < UMyGameInstance::GetInstance()->GetUIManagerInstance()->playerHitIndicators.Num(); i++)
	//{
	//	UMyGameInstance::GetInstance()->GetUIManagerInstance()->playerHitIndicators[i].LinkedImage = imageArray[i];
	//}

	//Copy the array from the UI Manager
	hitArray = UMyGameInstance::GetInstance()->GetUIManagerInstance()->playerHitIndicators;
	//Give references to the UI manager
	for (int i = 0; i < hitArray.Num(); i++)
	{
		hitArray[i].LinkedImage = imageArray[i];
		hitArray[i].LinkedBackground = spriteArray[i];
	}

	//Calculate the rate and stuff.
	for (int i = 0; i < hitArray.Num(); i++)
	{
		if (hitArray[i].LinkedImage != nullptr)
		{
			//Always set the visibility of image.
			hitArray[i].LinkedImage->SetVisibility(ESlateVisibility::Visible);
		}
		if (hitArray[i].LinkedBackground != nullptr)
		{
			//Always set the visibility of image.
			hitArray[i].LinkedBackground->SetVisibility(ESlateVisibility::Visible);
		}

		//Check for material now
		if (hitArray[i].MaterialInstance == nullptr)
		{
			hitArray[i].MaterialInstance = UMaterialInstanceDynamic::Create(MainMaterial, this);
			hitArray[i].MainTexture = MainTexture;
			hitArray[i].ApplyToMaterial();
			hitArray[i].ApplyToImage(imageArray[i]);
		}

		//Set the rotation of the image
		hitArray[i].LinkedImage->SetRenderTransformAngle(hitArray[i].playerHitParameters.rotation);
		hitArray[i].LinkedBackground->SetRenderTransformAngle(hitArray[i].playerHitParameters.rotation);

		if (hitArray[i].playerHitParameters.calculateRate)
		{
			hitArray[i].playerHitParameters.delayTimer = hitArray[i].playerHitParameters.delay;
			hitArray[i].UpdateFillAmount(InDeltaTime);
		}
		else
		{
			if (hitArray[i].playerHitParameters.delayTimer > 0)
				hitArray[i].playerHitParameters.delayTimer -= InDeltaTime;
			else
				hitArray[i].UpdateFillAmount(InDeltaTime);
		}

	}

	//Update back the UIManager
	UMyGameInstance::GetInstance()->GetUIManagerInstance()->playerHitIndicators = hitArray;
}
