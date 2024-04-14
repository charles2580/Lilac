// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "LilBTTask_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ULilBTTask_ChangeSpeed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit ULilBTTask_ChangeSpeed(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float speed = 120.0f;
};
