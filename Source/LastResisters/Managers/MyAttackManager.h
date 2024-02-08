// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LASTRESISTERS_API MyAttackManager
{
public:
	struct Attack_Info
	{
		FFloat16 info_CountdownTimer;
		FFloat16 info_BlockTimeWindow;
		FFloat16 info_Rotation;
		FVector info_Position;
		FString info_EnemyID;

		Attack_Info()
			: info_CountdownTimer(1)
			, info_BlockTimeWindow(1)
			, info_Rotation(0)
			, info_Position(FVector(0, 0, 0))
			, info_EnemyID(FString("monkaS"))
		{}
	};
	
	TArray<AAIController*> myListOfAI1;
	TArray<Attack_Info> myListOfAttacks;

	MyAttackManager();
	~MyAttackManager();

	bool AddToListOfAttacks(Attack_Info _info);
	bool AddToListOfAI1(AAIController* _aiCon);
	bool PrintOutListOfAttacks();
	bool PrintOutListOfAI1();

	void Update(float deltaTime);
	void UpdateAllAttacks(float _dt);
	
	void DamageTheAI(FString _ID);
};
