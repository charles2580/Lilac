// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"
#include "LilPlayer.h"
void UPlayerAttackState::OnEnterState(AActor* newActor, float deltaTime)
{
	stateManager = Cast<ALilPlayer>(newActor)->StateManager;
}

void UPlayerAttackState::UpdateState(AActor* newActor, float deltaTime) //Àû °ø°Ý
{
	if (Cast<ALilPlayer>(newActor)->Enemy)
	{
		Cast<ALilPlayer>(newActor)->Attack();
	}
	stateManager->ChangeState(UPlayerSearchState::StaticClass());
}

void UPlayerAttackState::OnExitState()
{
	stateManager = NULL;
}
