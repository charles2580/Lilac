// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBTTask_SetTargetEnemy.h"
#include "LilPlayerAIController.h"

ULilBTTask_SetTargetEnemy::ULilBTTask_SetTargetEnemy(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "SetTargetEnemy";
}

EBTNodeResult::Type ULilBTTask_SetTargetEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ALilPlayerAIController>(OwnerComp.GetAIOwner()))
	{
		cont->SetTarget();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
