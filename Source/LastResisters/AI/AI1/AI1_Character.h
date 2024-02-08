// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI1_Character.generated.h"

UCLASS()
class LASTRESISTERS_API AAI1_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI1_Character();

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* m_behaviorTree;

	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* m_pawnSensingComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnSeePlayer(APawn* _pawn);

	APawn* m_thePlayerPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
