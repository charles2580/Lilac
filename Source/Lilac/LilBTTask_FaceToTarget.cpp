// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBTTask_FaceToTarget.h"
#include "LilPlayerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ULilBTTask_FaceToTarget::ULilBTTask_FaceToTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "FaceToTarget";
}

EBTNodeResult::Type ULilBTTask_FaceToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	auto* blackboard = OwnerComp.GetBlackboardComponent();
	if (!blackboard) { return EBTNodeResult::Failed; }
	//BlackBoard로 부터 Target 받아오기
	AActor* target = Cast<AActor>(blackboard->GetValueAsObject(TEXT("Target")));
	if (!target) { return EBTNodeResult::Failed; }
	FVector targetloc = target->GetActorLocation();
	
	if (auto* const cont = OwnerComp.GetAIOwner())
	{
		if (auto const owner = Cast<AActor>(cont->GetPawn()))
		{
			FVector ownerDirection = (targetloc - owner->GetActorLocation()).GetSafeNormal();
			FRotator newDirection = ownerDirection.Rotation();
			newDirection.Pitch = owner->GetActorRotation().Pitch;
			newDirection.Roll = owner->GetActorRotation().Roll;
			owner->SetActorRotation(newDirection);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
