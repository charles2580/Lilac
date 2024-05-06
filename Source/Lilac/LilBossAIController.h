// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LilBossAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class LILAC_API ALilBossAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	explicit ALilBossAIController(FObjectInitializer const& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* APawn)override;

private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;

};
