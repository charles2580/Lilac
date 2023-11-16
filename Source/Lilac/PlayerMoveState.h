// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "PlayerMoveState.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UPlayerMoveState : public UObject, public IBaseState
{
	GENERATED_BODY()

private:
	AActor* targetActor = nullptr;
	FVector targetLocation = FVector::ZeroVector;

public:
	virtual void OnEnterState(AActor* newActor) override;
	virtual void UpdateState(AActor* newActor, float deltaTime) override;
	virtual void OnExitState() override;
};
