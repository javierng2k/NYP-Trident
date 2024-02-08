// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUIManager.h"

MyUIManager::MyUIManager()
{

}

MyUIManager::~MyUIManager()
{
}

void MyUIManager::Update(float deltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("UI UPDATE"));
	int indexOfAvailable = FindNextAvailableImage();
	if (indexOfAvailable != -1)
	{
		if (additionalRequests.Num() > 0)
		{
			MyAttackManager::Attack_Info info = additionalRequests[0];
			UE_LOG(LogTemp, Warning, TEXT("Taking Name : %s , Position : (%f, %f, %f), Rotation : (%f), Duration : (%f) into Index[%d]")
				, *info.info_EnemyID
				, info.info_Position.X
				, info.info_Position.Y
				, info.info_Position.Z
				, (float)info.info_Rotation
				, (float)info.info_CountdownTimer
				, indexOfAvailable);
			//We assign the additionalRequests first to try to catch up
			UE_LOG(LogTemp, Warning, TEXT("----BEFORE----"));
			playerHitIndicators[indexOfAvailable].PrintDetails();
			playerHitIndicators[indexOfAvailable].AssignParametersFromInfo(info);
			UE_LOG(LogTemp, Warning, TEXT("----AFTER----"));
			playerHitIndicators[indexOfAvailable].PrintDetails();

			//Then we removed the first variable we took
			additionalRequests.RemoveAt(0);
			//And then we re-organize the array.
			additionalRequests.Shrink();
		}
	}

}

int MyUIManager::FindNextAvailableImage()
{
	for (int i = 0; i < playerHitIndicators.Num(); i++)
	{
		//Check if the image is available.
		if (playerHitIndicators[i].playerHitParameters.duration > 0) // the image is still in use.
			continue;

		//Else it actually worked and it was able to find
		return i;
	}

	//It was unable to find cause they are too many attacks.
	return -1;
}

void MyUIManager::TakeInfoFromRequestQueue()
{
	//Take the first added element and then shrink.
	//The nearest available image should take from the queue.
}

void MyUIManager::HandleInit(MyAttackManager::Attack_Info infoToReceive)
{
	UE_LOG(LogTemp, Warning, TEXT("-----Player UI HandleInit Invoked-----"));
	UE_LOG(LogTemp, Warning, TEXT("Received MyCharacter's Name is %s , Robot Position : (%f, %f, %f), Rotation : (%f), Duration : (%f)")
		, *infoToReceive.info_EnemyID
		, infoToReceive.info_Position.X
		, infoToReceive.info_Position.Y
		, infoToReceive.info_Position.Z
		, (float)infoToReceive.info_Rotation
		, (float)infoToReceive.info_CountdownTimer);

	//When an init comes, we prioritise the additional request queue first because it came first.
	//Else it is just added to the request queue.

	//If the size is zero then I will add just once
	if (playerHitIndicators.Num() == 0)
	{
		playerHitIndicators.Add(FPlayerHitIndicator());
		UE_LOG(LogTemp, Warning, TEXT("Added first entry to hit indicators. It now has size : %d"), playerHitIndicators.Num());
	}

	//UE_LOG(LogTemp, Warning, TEXT("---BEFORE---"));
	//Find the next available image
	int indexOfAvailable = FindNextAvailableImage();
	//UE_LOG(LogTemp, Warning, TEXT("Index chosen: %d"),indexOfAvailable);

	//playerHitIndicators[indexOfAvailable].PrintDetails();

	//If we cant find a image then we add to additional requests.
	if (indexOfAvailable == -1)
	{
		//If it cant find... and the number is less than max UI
		if (playerHitIndicators.Num() < maxUI)
		{
			//Add a new entry
			playerHitIndicators.Add(FPlayerHitIndicator());
			//And set the index available to be the newest one
			indexOfAvailable = playerHitIndicators.Num() - 1;
			//Assign the information as well.
			playerHitIndicators[indexOfAvailable].AssignParametersFromInfo(infoToReceive);

			//UE_LOG(LogTemp, Warning, TEXT("Added new entry to hit indicators. It now has size : %d"), playerHitIndicators.Num());
			playerHitIndicators[indexOfAvailable].PrintDetails();
		}
		else
		{
			//If its default then theres no available images
			additionalRequests.Add(infoToReceive);
			//UE_LOG(LogTemp, Warning, TEXT("Added new entry to additional requests. It now has size : %d"), additionalRequests.Num());
		}
	}
	else
	{
		//Now we have available images, but we want to show the additionalRequests first before we process this.
		if (additionalRequests.Num() > 0)
		{
			MyAttackManager::Attack_Info info = additionalRequests[0];
			//We assign the additionalRequests first to try to catch up
			playerHitIndicators[indexOfAvailable].AssignParametersFromInfo(info);

			//Then we removed the first variable we took
			additionalRequests.RemoveAt(0);
			//And then we re-organize the array.
			additionalRequests.Shrink();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("SET VALUE"));
			//We assign the info from the pass in
			playerHitIndicators[indexOfAvailable].AssignParametersFromInfo(infoToReceive);
			//playerHitIndicators[indexOfAvailable].PrintDetails();
		}
	}
	//PrintIndicatorList();
}


void MyUIManager::HandleDelete(FString nameToDelete)
{
	UE_LOG(LogTemp, Warning, TEXT("-----Player UI HandleDelete Init Invoked-----"));
}

void MyUIManager::PrintIndicatorList()
{
	UE_LOG(LogTemp, Warning, TEXT("----PRINTING OF LIST----"))
	for (int i = 0; i < playerHitIndicators.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("----Index: %d----"), i);
		playerHitIndicators[i].PrintDetails();
	}
}
