// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UPlayerStateMachine : public UObject
{
	GENERATED_BODY()

protected:
	UPlayerStateMachine* PlayerSearchState = nullptr;
	UPlayerStateMachine* PlayerMoveState = nullptr;
	UPlayerStateMachine* PlayerAttackState = nullptr;
	UPlayerStateMachine* CurrentState = nullptr;

protected:
	virtual void ChangeState(UPlayerStateMachine* NewState);
};
