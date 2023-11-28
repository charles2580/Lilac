// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "PlayerStateMachine.h"
#include "PlayerAttackState.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UPlayerAttackState : public UObject, public IBaseState
{
	GENERATED_BODY()

public:
	virtual void OnEnterState(AActor* newActor, float deltaTime) override;
	virtual void UpdateState(AActor* newActor, float deltaTime) override;
	virtual void OnExitState() override;

private:
	UPlayerStateMachine* StateManager;
};
