// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"
#include "LilPlayer.h"
void UPlayerAttackState::OnEnterState(AActor* newActor, float deltaTime)
{
	player = Cast<ALilPlayer>(newActor);
	StateManager = Cast<ALilPlayer>(newActor)->StateManager;
}

void UPlayerAttackState::UpdateState(AActor* newActor, float deltaTime) //Àû °ø°Ý
{
	Cast<ALilPlayer>(newActor)->Attack();
}

void UPlayerAttackState::OnExitState()
{
	player = NULL;
	StateManager = NULL;
}
