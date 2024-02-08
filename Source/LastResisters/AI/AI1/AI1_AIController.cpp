// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_AIController.h"
#include "AI1_Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI1_PatrolTargetPoint.h"
#include "Components/CapsuleComponent.h"
#include "Managers/MyAttackManager.h"
#include "MyGameInstance.h"

AAI1_AIController::AAI1_AIController()
{
	m_behaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	m_blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AAI1_AIController::OnPossess(APawn * _pawn)
{
	Super::OnPossess(_pawn);

	AAI1_Character* aiChar_ = Cast<AAI1_Character>(_pawn);

	m_colliderRadius = aiChar_->GetCapsuleComponent()->GetScaledCapsuleRadius();
	m_colliderHalfHeight = aiChar_->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	m_colliderLengthCheck = sqrtf(m_colliderRadius * m_colliderRadius + m_colliderHalfHeight * m_colliderHalfHeight);

	if (aiChar_)
	{ // If valid as AAI1_Character
		if (aiChar_->m_behaviorTree->BlackboardAsset)
		{
			m_blackboardComp->InitializeBlackboard(*(aiChar_->m_behaviorTree->BlackboardAsset));
		}

		// Populate array with patrol target points
		//UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AAI1_PatrolTargetPoint::StaticClass(), a, m_patrolPoints);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI1_PatrolTargetPoint::StaticClass(), m_patrolPoints);

		if (m_patrolPoints.Num() == 0)
		{ // Prevent crashes, if there are no patrol points, the AI will be stationed at its spawned location
			for (int i = 0; i < 2; i++)
			{
				m_patrolPoints.Add(
					// Spawn and add to patrol points
					GetWorld()->SpawnActor<AAI1_PatrolTargetPoint>(AAI1_PatrolTargetPoint::StaticClass(), aiChar_->GetActorLocation(), FRotator(0, 0, 0), FActorSpawnParameters())
				);
			}
		}
		else
		{
			for (int i = 0; i < m_patrolPoints.Num(); i++)
			{
				FString temp = m_patrolPoints[i]->GetName();
				if (!temp.Contains(aiChar_->GetName()))
				{ // If the patrol point does not belong to the AI
					m_patrolPoints.RemoveAt(i, 1, true);
					i--;
				}
			}
		}

		//Start the behavior tree which corresponds to the specific character
		m_behaviorComp->StartTree(*aiChar_->m_behaviorTree);

		// Add to list of AI1
		UMyGameInstance::GetInstance()->GetAttackManagerInstance()->AddToListOfAI1(this);
		UMyGameInstance::GetInstance()->GetAttackManagerInstance()->PrintOutListOfAI1();
	}
}

void AAI1_AIController::SetSeenPlayer(APawn * _pawn)
{
	if (m_blackboardComp)
	{
		if (_pawn->IsPlayerControlled())
		{ // If can see player
			// Set visibility and target location
			m_blackboardComp->SetValueAsBool("canSeePlayer", true);
			m_blackboardComp->SetValueAsVector("targetLocation", _pawn->GetActorLocation());
		}
	}
}
