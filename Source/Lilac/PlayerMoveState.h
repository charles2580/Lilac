// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "PlayerStateMachine.h"
#include "PlayerAttackState.h"
#include "PlayerMoveState.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UPlayerMoveState : public UObject, public IBaseState
{
	GENERATED_BODY()

private:
	AActor* player = nullptr;
	AActor* targetActor = nullptr;
	FVector targetLocation = FVector::ZeroVector;
	UPlayerStateMachine* StateManager;
	UAnimInstance* AnimInstance;
public:
	virtual void OnEnterState(AActor* newActor, float deltaTime) override;
	virtual void UpdateState(AActor* newActor, float deltaTime) override;
	virtual void OnExitState() override;

private:
	bool isMoving;
	float moveSpeed;
};
