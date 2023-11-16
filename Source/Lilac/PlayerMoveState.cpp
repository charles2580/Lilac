// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoveState.h"
#include "LilPlayer.h"

void UPlayerMoveState::OnEnterState(AActor* newActor)
{
	targetActor = Cast<ALilPlayer>(newActor)->Enemy;
	targetLocation = targetActor->GetActorLocation();
}

void UPlayerMoveState::UpdateState(AActor* newActor, float deltaTime)
{

}

void UPlayerMoveState::OnExitState()
{
	targetActor = nullptr;
	targetLocation = FVector::ZeroVector;
}
