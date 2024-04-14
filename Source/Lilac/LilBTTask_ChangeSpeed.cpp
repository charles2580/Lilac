// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBTTask_ChangeSpeed.h"
#include "LilBaseCharacter.h"
#include "LilEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ULilBTTask_ChangeSpeed::ULilBTTask_ChangeSpeed(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Change Speed";
}

EBTNodeResult::Type ULilBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = OwnerComp.GetAIOwner())
	{
		if (auto const enemy = Cast<ALilBaseCharacter>(cont->GetPawn()))
		{
			enemy->ChangeSpeed(speed);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
