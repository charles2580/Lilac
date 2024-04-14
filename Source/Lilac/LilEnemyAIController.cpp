// Fill out your copyright notice in the Description page of Project Settings.


#include "LilEnemyAIController.h"
#include "LilEnemy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


ALilEnemyAIController::ALilEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/AI/EenmyAI/BT_Enemy.BT_Enemy'"));
    if (obj .Succeeded())
    {
        btree = obj.Object;
    }
    behavior_tree_Comp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
    blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void ALilEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(btree);
    behavior_tree_Comp->StartTree(*btree);
}

void ALilEnemyAIController::OnPossess(APawn* APawn)
{
    Super::OnPossess(APawn);

    if (blackboard)
    {
        blackboard->InitializeBlackboard(*btree->BlackboardAsset);
    }

    /*if (ALilEnemy* const enemy = Cast<ALilEnemy>(APawn))
    {
        if (UBehaviorTree* const tree = enemy->GetBehaviorTree())
        {
            UBlackboardComponent* BlackboardComp;
            UseBlackboard(tree->BlackboardAsset, BlackboardComp);
            Blackboard = BlackboardComp;
            RunBehaviorTree(tree);
            UE_LOG(LogTemp, Log, TEXT("hahaha"));
        }
    }*/
}
