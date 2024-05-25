// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "LilBTTask_FaceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ULilBTTask_FaceToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit ULilBTTask_FaceToTarget(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
