// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LilBaseCharacter.h"
#include "LilBoss.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ALilBoss : public ALilBaseCharacter
{
	GENERATED_BODY()
	
public: ALilBoss();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


	virtual void Attack() override;
	void Set_Montage(UAnimMontage* AttackMontage);

	UAnimMontage* BossAttack_Montage;

};
