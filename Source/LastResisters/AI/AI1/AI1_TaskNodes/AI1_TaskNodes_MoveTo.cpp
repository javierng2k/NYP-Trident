// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_MoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI1/AI1_AIController.h"

EBTNodeResult::Type UAI1_TaskNodes_MoveTo::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());

	if (aiCon_)
	{
		// If the AI has moved to the target location
		if (EPathFollowingRequestResult::AlreadyAtGoal == 
			aiCon_->MoveToLocation(aiCon_->GetBlackboardComp()->GetValueAsVector("targetLocation"), aiCon_->GetCombatRange(), true, true, true, true, 0, true))
		{
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
