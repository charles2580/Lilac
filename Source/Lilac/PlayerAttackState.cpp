// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"
#include "LilPlayer.h"
void UPlayerAttackState::OnEnterState(AActor* newActor, float deltaTime)
{
	stateManager = Cast<ALilPlayer>(newActor)->StateManager;
}

void UPlayerAttackState::UpdateState(AActor* newActor, float deltaTime) //Àû °ø°Ý
{
	ALilPlayer* player = Cast<ALilPlayer>(newActor);
	if (player && player->Enemy->CheckStillInWorld())
	{
		player->Attack();
	}
	else
	{
		stateManager->ChangeState(UPlayerSearchState::StaticClass());
	}
}

void UPlayerAttackState::OnExitState()
{
	stateManager = NULL;
}
