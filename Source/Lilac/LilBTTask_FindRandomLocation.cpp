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
	if (auto* const cont = OwnerComp.GetAIOwner()) //현재 behaviorTree를 실행시킨 ai컨트롤러
	{
		if (auto* const Enemy = cont->GetPawn()) //ai 컨트롤러를 소유하고 있는 pawn
		{
			auto const Origin = Enemy->GetActorLocation();

			if (auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld())) // 현재 월드의 네비게이션 시스템
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
