// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LilEnemyAIController.h"

ULilBTTask_FindRandomLocation::ULilBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type ULilBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ALilEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const Enemy = cont->GetPawn())
		{
			auto const Origin = Enemy->GetActorLocation();

			if (auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				
				if (Nav->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					Loc.Location.Z = Origin.Z;
					cont->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}
				
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}	
	}
	return EBTNodeResult::Failed;
}	
