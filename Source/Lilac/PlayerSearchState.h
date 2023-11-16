// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
//#include "Kismet/GameplayStatics.h"
//#include "PlayerStateMachine.h"
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

private:
	AActor* targetActor = nullptr;
	FVector playerLocation = FVector::ZeroVector;
	USphereComponent* sphereCollider = nullptr;
	//UPlayerStateMachine* StateManager;
public:
	virtual void OnEnterState(AActor* newActor) override;
	virtual void UpdateState(AActor* newActor, float deltaTime) override;
	virtual void OnExitState() override;

private:
	AActor* SearchTarget(AActor* newActor);
};
