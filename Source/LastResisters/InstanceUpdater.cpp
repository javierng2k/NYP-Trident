// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceUpdater.h"
#include "MyGameInstance.h"

// Sets default values
AInstanceUpdater::AInstanceUpdater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInstanceUpdater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInstanceUpdater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Update all stuff
	UMyGameInstance::GetInstance()->Update(DeltaTime);
	
}

