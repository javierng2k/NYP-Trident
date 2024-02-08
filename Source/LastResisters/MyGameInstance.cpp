// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/Engine.h"

#include "Managers/MyUIManager.h"
#include "Managers/MyPlayerManager.h"
#include "Managers/MyAttackManager.h"

void UMyGameInstance::Init()
{
	m_UIManager = new MyUIManager();
	m_playerManager = new MyPlayerManager();
	m_attackManager = new MyAttackManager();
}

void UMyGameInstance::Shutdown()
{
	if (m_UIManager)
	{
		delete m_UIManager;
		m_UIManager = NULL;
	}

	if (m_playerManager)
	{
		delete m_playerManager;
		m_playerManager = NULL;
	}

	if (m_attackManager)
	{
		delete m_attackManager;
		m_attackManager = NULL;
	}
}

UMyGameInstance* UMyGameInstance::GetInstance()
{
	UMyGameInstance* instance = nullptr;

	if (GEngine)
	{
		FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		instance = Cast<UMyGameInstance>(context->OwningGameInstance);
	}

	return instance;
}

MyUIManager * UMyGameInstance::GetUIManagerInstance()
{
	if (m_UIManager)
	{
		return m_UIManager;
	}
	return nullptr;
}

MyPlayerManager * UMyGameInstance::GetPlayerManagerInstance()
{
	if (m_playerManager)
	{
		return m_playerManager;
	}
	return nullptr;
}

MyAttackManager * UMyGameInstance::GetAttackManagerInstance()
{
	if (m_attackManager)
	{
		return m_attackManager;
	}
	return nullptr;
}

void UMyGameInstance::Update(float inDeltaTime)
{
	m_UIManager->Update(inDeltaTime);
	m_playerManager->Update(inDeltaTime);
	m_attackManager->Update(inDeltaTime);
}

