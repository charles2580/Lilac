// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "PlayerStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UPlayerStateMachine : public UObject
{
	GENERATED_BODY()

public:
	void ChangeState(TSubclassOf<UObject> NewStateClass);
	void Update(float DelatTime);
	void ExitState();

public:
	UObject* CurrentState = nullptr;
	AActor* player = nullptr;

private:
	float deltaTime = 0;
};
