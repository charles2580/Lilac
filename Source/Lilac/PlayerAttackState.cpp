// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"
#include "LilPlayer.h"
void UPlayerAttackState::OnEnterState(AActor* newActor, float deltaTime)
{
	stateManager = Cast<ALilPlayer>(newActor)->StateManager;
}

void UPlayerAttackState::UpdateState(AActor* newActor, float deltaTime) //Àû °ø°Ý
{
	ALilPlayer* player = Cast<ALilPlayer>(newActor);
	if (player)
	{
		if (player->Enemy->CheckStillInWorld())
		{
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
