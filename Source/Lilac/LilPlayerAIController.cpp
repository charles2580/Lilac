// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayerAIController.h"
#include "LilPlayer.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ALilPlayerAIController::ALilPlayerAIController(FObjectInitializer const& ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/AI/PlayerAI/BT_Player.BT_Player'"));
    if (obj.Succeeded())
    {
        btree = obj.Object;
    }
    behavior_tree_Comp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
    blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
    targetUpdate_Interval = 3.0f;
}

void ALilPlayerAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(btree);
    behavior_tree_Comp->StartTree(*btree);
}

void ALilPlayerAIController::OnPossess(APawn* APawn)
{
    Super::OnPossess(APawn);

    if (blackboard)
    {
        blackboard->InitializeBlackboard(*btree->BlackboardAsset);
    }
    SetTarget();
    GetWorldTimerManager().SetTimer(TimerHandle_UpdateTarget, this, &ALilPlayerAIController::SetTarget, targetUpdate_Interval, true);
}

void ALilPlayerAIController::OnUnPossess()
{

    GetWorldTimerManager().ClearTimer(TimerHandle_UpdateTarget);
    Super::OnUnPossess();
}

void ALilPlayerAIController::SetTarget()
{
    UE_LOG(LogTemp, Log, TEXT("hahaha"));
    ALilPlayer* player = Cast<ALilPlayer>(GetPawn());
    if (player && blackboard)
    {
        blackboard->SetValueAsObject(TEXT("Target"), player->GetTarget());
    }
}
