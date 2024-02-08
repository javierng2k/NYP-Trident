// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_TaskNodes_StateManagement.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI1/AI1_AIController.h"
#include "AIController.h"
#include "MyGameInstance.h"
#include "Managers/MyAttackManager.h"
#include "../../../UI/PlayerUI/PlayerHitUI/PlayerHitUI.h"

EBTNodeResult::Type UAI1_TaskNodes_StateManagement::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI1_AIController* aiCon_ = Cast<AAI1_AIController>(OwnerComp.GetAIOwner());
	if (!aiCon_)
		return EBTNodeResult::Failed;

	// Get all necessary values for state management
	m_bbComp = aiCon_->GetBlackboardComp();
	m_currState = m_bbComp->GetValueAsEnum("currState");
	m_canSeePlayer = m_bbComp->GetValueAsBool("canSeePlayer");
	m_combatRange = aiCon_->GetCombatRange() + aiCon_->GetColliderLengthCheck();

	switch (m_currState)
	{
		case 0:
		{ // Patrol state
			if (m_canSeePlayer)
			{ // If can see player
				// Change state to chase state
				ChangeState(1);
			}
		} break;

		case 1:
		{ // Chase state
			FVector targetLocation = m_bbComp->GetValueAsVector("targetLocation");
			FVector myPosition = aiCon_->GetPawn()->GetActorLocation();
			FFloat16 dist_ = FVector::Dist(targetLocation, myPosition);

			if (dist_ <= m_combatRange)
			{ // If within range of target			

				if (!m_canSeePlayer)
				{ // If cannot see player
					// Change state to alert state
					ChangeState(2);
				}
				else
				{ // If can see player
					// Change state to combat state
					ChangeState(3);
				}
			}
		} break;

		case 2:
		{ // Alert state
			if (!m_canSeePlayer)
			{ // If cannot see player
				// Change state to patrol
				ChangeState(0);
			}
			else
			{ // If can see player
				// Change state to chase
				ChangeState(1);
			}
		} break;

		case 3:
		{ // Combat state
			if (!m_canSeePlayer)
			{ // If cannot see player
				// Change state to patrol
				ChangeState(0);
			}

			FVector targetLocation = m_bbComp->GetValueAsVector("targetLocation");
			FVector myPosition = aiCon_->GetPawn()->GetActorLocation();
			FFloat16 dist_ = FVector::Dist(targetLocation, myPosition);
			if (dist_ > m_combatRange)
			{ // If player ran away
				// Change state to chase
				ChangeState(1);
			}
		} break;

		default:
		{
		} break;
	}


	return EBTNodeResult::Succeeded;
}

void UAI1_TaskNodes_StateManagement::ChangeState(int _state)
{
	m_bbComp->SetValueAsEnum("currState", _state);

	switch (_state)
	{
		case 3:
		{ // If changing currState to combat
			// Set stance to ready
			m_bbComp->SetValueAsEnum("currStance", 0);
		} break;
		default:
		{
		} break;
	}
}
