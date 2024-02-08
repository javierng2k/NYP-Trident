// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI1_TaskNodes_StateManagement.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESISTERS_API UAI1_TaskNodes_StateManagement : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBlackboardComponent* m_bbComp;
	uint8 m_currState;
	bool m_canSeePlayer;
	FFloat16 m_combatRange;

	void ChangeState(int _state);
};
