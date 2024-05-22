// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "PlayerStateMachine.h"
#include "Components/SphereComponent.h"
#include "PlayerSearchState.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UPlayerSearchState : public UObject, public IBaseState
{
	GENERATED_BODY()
	
public:
	// »ý¼ºÀÚ
	//UPlayerSearchState(UPlayerStateMachine* InStateMachine) : StateManager(InStateMachine) {}

	USphereComponent* sphereCollider;

private:
	AActor* targetActor = nullptr;
	FVector playerLocation = FVector::ZeroVector;
	UPlayerStateMachine* StateManager;

public:
	virtual void OnEnterState(AActor* newActor, float deltaTime) override;
	virtual void UpdateState(AActor* newActor, float deltaTime) override;
	virtual void OnExitState() override;

private:
	AActor* SearchTarget(AActor* newActor);
};
