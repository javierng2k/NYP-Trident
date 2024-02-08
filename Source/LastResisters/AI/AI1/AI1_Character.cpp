// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1_Character.h"
#include "AI1_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AAI1_Character::AAI1_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Initializing the pawn sensing component
	m_pawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degree
	m_pawnSensingComp->SetPeripheralVisionAngle(90.0f);		
}

// Called when the game starts or when spawned
void AAI1_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAI1_Character::OnSeePlayer(APawn * _pawn)
{
	AAI1_AIController* AIController = Cast<AAI1_AIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		AIController->SetSeenPlayer(_pawn);
		m_thePlayerPawn = _pawn;
	}
}

// Called every frame
void AAI1_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Register the function that is going to fire when the character sees a Pawn
	if (m_pawnSensingComp)
	{
		m_pawnSensingComp->OnSeePawn.AddDynamic(this, &AAI1_Character::OnSeePlayer);
	}

	if (m_thePlayerPawn)
	{
		if (!m_pawnSensingComp->CouldSeePawn(m_thePlayerPawn) || !m_pawnSensingComp->HasLineOfSightTo(m_thePlayerPawn))
		{
			
			AAI1_AIController* AIController = Cast<AAI1_AIController>(GetController());
			if (AIController)
			{
				AIController->GetBlackboardComp()->SetValueAsBool("canSeePlayer", 0);
			}
		}
		else
		{
		}
	}
}

// Called to bind functionality to input
void AAI1_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

