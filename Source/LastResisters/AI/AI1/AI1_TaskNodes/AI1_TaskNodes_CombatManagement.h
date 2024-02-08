// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI1_TaskNodes_CombatManagement.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESISTERS_API UAI1_TaskNodes_CombatManagement : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBlackboardComponent* m_bbComp;
	uint8 m_currStance;

	//bool m_isReady = false;
	//float m_prevWorldTime = 0.0f;
	//float m_readyTimer = 0.0f;
	//const float m_readyTime = 2.0f;

	void ChangeStance(int _stance);
};
