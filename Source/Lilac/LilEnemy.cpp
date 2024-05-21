// Fill out your copyright notice in the Description page of Project Settings.


#include "LilEnemy.h"
#include "LilEnemyAIController.h"

ALilEnemy::ALilEnemy()
{
	PriorityID = FPriorityID(2, "Enemy");

	AIControllerClass = ALilEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	enemy_movc = GetCharacterMovement();
}

void ALilEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ALilEnemy::Attack()
{
	Super::Attack();

	UAnimInstance* animInst = GetMesh()->GetAnimInstance();
	if (animInst)
	{
		if (EnemyAttack_Montage)
		{
			if (!animInst->Montage_IsPlaying(EnemyAttack_Montage))
			{
				animInst->Montage_Play(EnemyAttack_Montage);
			}
		}		
	}
}

void ALilEnemy::OnSeePawn(APawn* Pawn)
{
	//타겟설정
}

void ALilEnemy::OnSeePawnHandler()
{
	//ai controller에 있어야함
}

void ALilEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
