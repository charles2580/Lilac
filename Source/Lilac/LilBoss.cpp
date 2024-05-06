// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBoss.h"

ALilBoss::ALilBoss()
{
	BossAttack_Montage = nullptr;
}

void ALilBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALilBoss::BeginPlay()
{
	Super::BeginPlay();
}

void ALilBoss::Attack()
{
	Super::Attack();

	UAnimInstance* animInst = GetMesh()->GetAnimInstance();
	if (animInst)
	{
		if (BossAttack_Montage)
		{
			if (!animInst->Montage_IsPlaying(BossAttack_Montage))
			{
				animInst->Montage_Play(BossAttack_Montage);
			}
		}
	}
}

void ALilBoss::Set_Montage(UAnimMontage* AttackMontage)
{
	BossAttack_Montage = AttackMontage;
}
