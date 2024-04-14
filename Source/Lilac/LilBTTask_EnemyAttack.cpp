// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBTTask_EnemyAttack.h"
#include "LilEnemyAIController.h"
#include "LilEnemy.h"

ULilBTTask_EnemyAttack::ULilBTTask_EnemyAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Enemy Attack";
}

EBTNodeResult::Type ULilBTTask_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ALilEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = Cast<ALilEnemy>(cont->GetPawn()) )
		{
			enemy->Enemy_Attack();
		}
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
