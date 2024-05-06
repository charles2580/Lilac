// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBossAIController.h"
#include "LilBoss.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ALilBossAIController::ALilBossAIController(FObjectInitializer const& ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/AI/BossAI/BT_Boss.BT_Boss'"));
    if (obj.Succeeded())
    {
        btree = obj.Object;
    }
    behavior_tree_Comp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
    blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void ALilBossAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(btree);
    behavior_tree_Comp->StartTree(*btree);
}

void ALilBossAIController::OnPossess(APawn* APawn)
{
    Super::OnPossess(APawn);

    if (blackboard)
    {
        blackboard->InitializeBlackboard(*btree->BlackboardAsset);
    }
}
