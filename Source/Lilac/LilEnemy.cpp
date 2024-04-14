// Fill out your copyright notice in the Description page of Project Settings.


#include "LilEnemy.h"
#include "LilEnemyAIController.h"

ALilEnemy::ALilEnemy()
{
	AIControllerClass = ALilEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	enemy_movc = GetCharacterMovement();
}

void ALilEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ALilEnemy::Enemy_Attack()
{
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
