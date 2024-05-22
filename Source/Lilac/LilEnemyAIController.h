// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LilEnemyAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;
class UBlackboardComponent;


UCLASS()
class LILAC_API ALilEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	explicit ALilEnemyAIController(FObjectInitializer const& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* APawn)override;


	//class UBlackboardComponent* get_blackboard() const;
private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;
};
