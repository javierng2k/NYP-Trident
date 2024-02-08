// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI1_TaskNodes_GoToOffenseStance.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESISTERS_API UAI1_TaskNodes_GoToOffenseStance : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBlackboardComponent* m_bbComp;
	
	void ChangeStance(int _stance);

	FFloat16 infoDuration1 = 2.0f;
	FFloat16 infoRotation1 = 30.0f;
	FFloat16 infoDuration2 = 1.5f;
	FFloat16 infoRotation2 = 60.0f;
	FFloat16 infoDuration3 = 1.0f;
	FFloat16 infoRotation3 = 120.0f;
	FFloat16 infoDuration4 = 1.3f;
	FFloat16 infoRotation4 = 10.0f;
};
