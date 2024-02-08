// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LASTRESISTERS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init();
	
	virtual void Shutdown();

	class MyUIManager * m_UIManager = nullptr;
	class MyPlayerManager * m_playerManager = nullptr;
	class MyAttackManager * m_attackManager = nullptr;

public:
	static UMyGameInstance* GetInstance();

	MyPlayerManager* GetPlayerManagerInstance();
	MyUIManager* GetUIManagerInstance();
	MyAttackManager* GetAttackManagerInstance();

	void Update(float inDeltaTime);
};
