// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"
#include "LilPlayer.h"
void UPlayerAttackState::OnEnterState(AActor* newActor, float deltaTime)
{
	stateManager = Cast<ALilPlayer>(newActor)->StateManager;
}

void UPlayerAttackState::UpdateState(AActor* newActor, float deltaTime) //적 공격
{
	ALilPlayer* player = Cast<ALilPlayer>(newActor);
	if (player)
	{
		FVector enemyLoc;
		float distance;
		if (player->Enemy)
		{
			enemyLoc = player->Enemy->GetActorLocation();
			distance = (enemyLoc - player->GetActorLocation()).Size();
		}
		if (player->Enemy->CheckStillInWorld() && distance < 150.0f )
		{
			FVector playerDirection = (enemyLoc - player->GetActorLocation()).GetSafeNormal(); //플레이어의 새로운 방향벡터
			FRotator newDirection = playerDirection.Rotation();
			player->SetActorRotation(newDirection); //플레이어가 타겟을 바라보게 함
			player->Attack();
		}
		else
		{
			UAnimInstance* animInst = player->GetMesh()->GetAnimInstance();
			if (animInst)
			{
				if (player->comboAttackMontage)
				{
					animInst->Montage_Stop(0.0f,player->comboAttackMontage);
				}
			}
			stateManager->ChangeState(UPlayerSearchState::StaticClass());
		}
	}
}

void UPlayerAttackState::OnExitState()
{
	stateManager = NULL;
}
