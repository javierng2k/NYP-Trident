// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_IncrementPathIndex.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI1/AI1_AIController.h"

EBTNodeResult::Type UAI1_TaskNodes_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());


	if (aiCon_)
	{
		// Get values from blackboard and AI controller
		UBlackboardComponent* bbComp_ = aiCon_->GetBlackboardComp();
		int32 patrolPathIndex_ = bbComp_->GetValueAsInt("patrolPathIndex");
		
		// Increment the index and loop back to 0 if exceeded
		patrolPathIndex_ += 1;
		if (patrolPathIndex_ >= aiCon_->GetAvailableTargetPoints().Num())
			patrolPathIndex_ = 0;

		// Set the Index
		bbComp_->SetValueAsInt("patrolPathIndex", patrolPathIndex_);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}