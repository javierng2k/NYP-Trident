// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_CombatManagement.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI1/AI1_AIController.h"
#include "AIController.h"
#include "TimerManager.h"

EBTNodeResult::Type UAI1_TaskNodes_CombatManagement::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());
	if (!aiCon_)
		return EBTNodeResult::Failed;

	// Get all necessary values for stance management
	m_bbComp = aiCon_->GetBlackboardComp();
	m_currStance = m_bbComp->GetValueAsEnum("currStance");

	switch (m_currStance)
	{
	case 0:
	{ // Ready stance
		
	} break;

	case 1:
	{ // Attack1 stance
	} break;

	case 2:
	{ // Attack2 stance
		
	} break;

	case 3:
	{ // Attack3 stance
		
	} break;

	default:
	{
	} break;
	}


	return EBTNodeResult::Succeeded;
}

void UAI1_TaskNodes_CombatManagement::ChangeStance(int _stance)
{
	m_bbComp->SetValueAsEnum("currState", _stance);
}