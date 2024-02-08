// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_FindPatrolLocation.h"
#include "AI/AI1/AI1_PatrolTargetPoint.h"
#include "AI/AI1/AI1_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAI1_TaskNodes_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());


	if (aiCon_)
	{
		// Get values from blackboard and AI controller
		UBlackboardComponent* bbComp_ = aiCon_->GetBlackboardComp();
		int32 patrolPathIndex_ = bbComp_->GetValueAsInt("patrolPathIndex");
		TArray<AActor*> availableTargetPoints_ = aiCon_->GetAvailableTargetPoints();

		// Set target location based on current patrol index
		bbComp_->SetValueAsVector("targetLocation", availableTargetPoints_[patrolPathIndex_]->GetActorLocation());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}