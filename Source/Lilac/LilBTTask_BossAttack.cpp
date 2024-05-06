// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBTTask_BossAttack.h"
#include "LilBoss.h"
#include "LilBossAIController.h"

ULilBTTask_BossAttack::ULilBTTask_BossAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "BossAttack";
}

EBTNodeResult::Type ULilBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (auto* const cont = OwnerComp.GetAIOwner())
	{
		if (auto const boss = Cast<ALilBoss>(cont->GetPawn()))
		{
			boss->Set_Montage(BossAttack_Montage);
			boss->Attack();
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	
	return EBTNodeResult::Failed;

}
