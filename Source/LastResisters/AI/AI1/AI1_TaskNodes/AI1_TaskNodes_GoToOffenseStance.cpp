// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_GoToOffenseStance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI1/AI1_AIController.h"
#include "AIController.h"
#include "Managers/MyAttackManager.h"
#include "MyGameInstance.h"

EBTNodeResult::Type UAI1_TaskNodes_GoToOffenseStance::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());
	if (!aiCon_)
		return EBTNodeResult::Failed;

	// Get all necessary values for state management
	m_bbComp = aiCon_->GetBlackboardComp();

	int32 randAtk_ = FMath::RandRange(1, 4);
	ChangeStance(randAtk_);

	// Send attack info to attack manager
	MyAttackManager::Attack_Info info_;
	info_.info_EnemyID = aiCon_->GetPawn()->GetName();
	info_.info_Position = aiCon_->GetPawn()->GetActorLocation();

	switch (randAtk_)
	{
	case 1:
	{
		info_.info_CountdownTimer = infoDuration1;
		info_.info_Rotation = infoRotation1;
	}
	break;
	case 2:
	{
		info_.info_CountdownTimer = infoDuration2;
		info_.info_Rotation = infoRotation2;
	}
	break;
	case 3:
	{
		info_.info_CountdownTimer = infoDuration3;
		info_.info_Rotation = infoRotation3;
	}
	break;
	case 4:
	{
		info_.info_CountdownTimer = infoDuration4;
		info_.info_Rotation = infoRotation4;
	}
	break;
	default:
		break;
	}

	UMyGameInstance::GetInstance()->GetAttackManagerInstance()->AddToListOfAttacks(info_);

	return EBTNodeResult::Succeeded;
}

void UAI1_TaskNodes_GoToOffenseStance::ChangeStance(int _stance)
{
	m_bbComp->SetValueAsEnum("currStance", _stance);

}
