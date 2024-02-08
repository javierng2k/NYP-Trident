// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_GoToReadyStance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI1/AI1_AIController.h"
#include "AIController.h"

EBTNodeResult::Type UAI1_TaskNodes_GoToReadyStance::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());
	if (!aiCon_)
		return EBTNodeResult::Failed;

	// Get all necessary values for state management
	m_bbComp = aiCon_->GetBlackboardComp();

	ChangeStance(0);

	return EBTNodeResult::Succeeded;
}

void UAI1_TaskNodes_GoToReadyStance::ChangeStance(int _stance)
{
	m_bbComp->SetValueAsEnum("currStance", _stance);

}