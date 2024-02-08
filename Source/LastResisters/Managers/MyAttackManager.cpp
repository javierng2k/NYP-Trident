// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttackManager.h"
#include "MyPlayerManager.h"
#include "MyGameInstance.h"
#include "UI/PlayerUI/PlayerHitUI/PlayerHitUI.h"
#include "AIController.h"
#include "AI/AI1/AI1_AIController.h"
#include "MyUIManager.h"

MyAttackManager::MyAttackManager()
{
}

MyAttackManager::~MyAttackManager()
{
}

bool MyAttackManager::AddToListOfAttacks(Attack_Info _info)
{
	if (!_info.info_EnemyID.IsEmpty())
	{
		// Init the attack to the UI
		UMyGameInstance::GetInstance()->GetUIManagerInstance()->HandleInit(_info);
		myListOfAttacks.Add(_info);

		return true;
	}
	return false;
}

bool MyAttackManager::AddToListOfAI1(AAIController* _aiCon)
{
	if (_aiCon)
	{
		myListOfAI1.Add(_aiCon);

		return true;
	}
	return false;
}

void MyAttackManager::Update(float deltaTime)
{
	UpdateAllAttacks(deltaTime);
}

void MyAttackManager::UpdateAllAttacks(float _dt)
{
	int sizeOfList = myListOfAttacks.Num();
	for (int i = 0; i < sizeOfList; i++)
	{
		// Update the countdown
		myListOfAttacks[i].info_CountdownTimer = myListOfAttacks[i].info_CountdownTimer - _dt; // -= doesnt work
		
		if (myListOfAttacks[i].info_CountdownTimer <= 0.0f)
		{ // If the attack was not blocked
			// Delete the attack from the UI
			UMyGameInstance::GetInstance()->GetUIManagerInstance()->HandleDelete(myListOfAttacks[i].info_EnemyID);

			DamageTheAI(myListOfAttacks[i].info_EnemyID);

			// Remove the attack from the list
			myListOfAttacks.RemoveAt(i);
			myListOfAttacks.Shrink();

			if (sizeOfList > 0)
			{ // If there are more things to check through in the list of attacks
				--i;
				--sizeOfList;
			}
			// Damage the player
			// TODO
		}
		else if (myListOfAttacks[i].info_CountdownTimer <= myListOfAttacks[i].info_BlockTimeWindow)
		{ // If attack can be blocked
			if (UMyGameInstance::GetInstance()->GetPlayerManagerInstance()->CheckIfBlocked(myListOfAttacks[i].info_Position, myListOfAttacks[i].info_Rotation))
			{ // If attack has been successfully blocked
				// Damage the AI's armor
				DamageTheAI(myListOfAttacks[i].info_EnemyID);

				// Delete the attack from the UI
				UMyGameInstance::GetInstance()->GetUIManagerInstance()->HandleDelete(myListOfAttacks[i].info_EnemyID);

				// Remove the attack from the list
				myListOfAttacks.RemoveAt(i);
				myListOfAttacks.Shrink();

				if (sizeOfList > 0)
				{ // If there are more things to check through in the list of attacks
					--i;
					--sizeOfList;
				}
			}
		}
	}
}

void MyAttackManager::DamageTheAI(FString _ID)
{
	for (int i = 0; i < myListOfAI1.Num(); i++)
	{
		AAI1_AIController* ai1Con_ = Cast<AAI1_AIController>(myListOfAI1[i]);

		if (ai1Con_)
		{
			if (ai1Con_->GetPawn()->GetName() == _ID)
			{
				ai1Con_->SetHP(0);
				UE_LOG(LogTemp, Warning, TEXT("I[HIT : %d] HP : (%f)")
					, i
					, ai1Con_->GetHP().GetFloat());
			}
		}
	}
}

bool MyAttackManager::PrintOutListOfAttacks()
{
	for (int i = 0; i < myListOfAttacks.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("I[Index : %d] MyCharacter's Name is %s , Robot Position : (%f, %f, %f), Rotation : (%f)")
			, i
			, *myListOfAttacks[i].info_EnemyID
			, myListOfAttacks[i].info_Position.X
			, myListOfAttacks[i].info_Position.Y
			, myListOfAttacks[i].info_Position.Z
			, (float)myListOfAttacks[i].info_Rotation);
	}
	return false;
}

bool MyAttackManager::PrintOutListOfAI1()
{
	for (int i = 0; i < myListOfAI1.Num(); i++)
	{
		AAI1_AIController* ai1Con_ = Cast<AAI1_AIController>(myListOfAI1[i]);

		if (ai1Con_)
		{

			UE_LOG(LogTemp, Warning, TEXT("I[Index : %d] HP : (%f)")
				, i
				, ai1Con_->GetHP().GetFloat());
		}
	}
	return false;
}
