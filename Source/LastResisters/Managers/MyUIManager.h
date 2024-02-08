// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAttackManager.h"
#include "../UI/PlayerUI/PlayerHitUI/PlayerHitIndicator.h"

/**
 * 
 */
class LASTRESISTERS_API MyUIManager
{
public:
	MyUIManager();
	~MyUIManager();

	//Amount of max UI
	const int maxUI = 5;

	//Update function
	void Update(float deltaTime);
	
	//Arrays that store information.
	TArray<FPlayerHitIndicator> playerHitIndicators;
	TArray<MyAttackManager::Attack_Info> additionalRequests;

	//Finds the next available image to use and assign
	 int FindNextAvailableImage();

	//Function that makes the next available image take info from request queue.
	 void TakeInfoFromRequestQueue();

	 //Handle functions
	 void HandleInit(MyAttackManager::Attack_Info infoToReceive);
	 void HandleDelete(FString nameToDelete);

	 //Prints every single indicator
	 void PrintIndicatorList();

	 //Functions and do rate stuff

};
