// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayerAIController.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

ALilPlayerAIController::ALilPlayerAIController(FObjectInitializer const& ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/AI/PlayerAI/BT_Player.BT_Player'"));
    if (obj.Succeeded())
    {
        btree = obj.Object;
    }
    behavior_tree_Comp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
    blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
    targetUpdate_Interval = 5.0f;
    target = nullptr;
}

void ALilPlayerAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ALilPlayerAIController::OnPossess(APawn* APawn)
{
    Super::OnPossess(APawn);

    if (blackboard)
    {
        blackboard->InitializeBlackboard(*btree->BlackboardAsset);
    }
    //탐지된 적 이름 표시 할 widget 생성
    gridWidget = CreateWidget<ULilPlayerWidget>(GetWorld(), playerWidget);
    if (gridWidget)
    {
        gridWidget->AddToViewport();
    }
    UpdateDetectedActor();
    GetWorldTimerManager().SetTimer(TimerHandle_UpdateTarget, this, &ALilPlayerAIController::UpdateDetectedActor, targetUpdate_Interval, true);
    RunBehaviorTree(btree);
    behavior_tree_Comp->StartTree(*btree);
}

void ALilPlayerAIController::OnUnPossess()
{

    GetWorldTimerManager().ClearTimer(TimerHandle_UpdateTarget);
    gridWidget->RemoveFromParent();
    Super::OnUnPossess();
    target = nullptr;
}

void ALilPlayerAIController::SetTarget()
{
    target = detectedActors[0];
    target->OnDestroyed.AddDynamic(this, &ALilPlayerAIController::OnTargetDestroyed);
    blackboard->SetValueAsObject(TEXT("Target"), target);
}

void ALilPlayerAIController::UpdateDetectedActor()
{
    ALilPlayer* player = Cast<ALilPlayer>(GetPawn());
    if (player)
    {
        player->GetDetectedActors(detectedActors);
        if (detectedActors.IsEmpty())
        {
            blackboard->SetValueAsBool(TEXT("isAnyDetectedActor"), false);
            return;
        }
        blackboard->SetValueAsBool(TEXT("isAnyDetectedActor"), true);
        
        detectedActors.Sort([this](const ALilBaseCharacter& A, const ALilBaseCharacter& B)
            {
                if (A.PriorityID.Priority == B.PriorityID.Priority)
                {
                    if (GetDistanceToTarget(A) > 0 && GetDistanceToTarget(B) > 0)
                    {
                        return GetDistanceToTarget(A) < GetDistanceToTarget(B);
                    }
                    //return FVector::Dist(player->GetActorLocation(), A.GetActorLocation()) < FVector::Dist(player->GetActorLocation(), B.GetActorLocation());
                }
                return A.PriorityID.Priority < B.PriorityID.Priority;
            }
        );

        if (detectedActors.Num() > 8)
        {
            detectedActors.SetNum(8);
        }
    }
    if (gridWidget)
    {
        gridWidget->UpdateTextBlocks(detectedActors);
    }
}

void ALilPlayerAIController::OnTargetDestroyed(AActor* DestroyedActor)
{
    target = nullptr;
    detectedActors.RemoveAt(0);
    blackboard->SetValueAsObject(TEXT("Target"), nullptr);
    gridWidget->UpdateTextBlocks(detectedActors);
}

float ALilPlayerAIController::GetDistanceToTarget(const ALilBaseCharacter& Target)
{
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSys)
    {
        ANavigationData* NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::ECreateIfEmpty::DontCreate);
        if (NavData)
        {
            FPathFindingQuery Query;
            FVector StartLocation = GetPawn()->GetActorLocation();
            FVector EndLocation = Target.GetActorLocation();
            UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(GetWorld(), StartLocation, EndLocation);
            if (NavPath->IsValid())
            {
                return NavPath->GetPathLength();
            }
        }
    }
    return -1.0f;
}
