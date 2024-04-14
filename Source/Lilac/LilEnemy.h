// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LilBaseCharacter.h"
#include "LilEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ALilEnemy : public ALilBaseCharacter
{
	GENERATED_BODY()
	

public: ALilEnemy();

	  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	  UAnimMontage* EnemyAttack_Montage;

	  virtual void Attack() override;
	
	  UCharacterMovementComponent* enemy_movc;
private:
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	void OnSeePawnHandler();

	APawn* target;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

};
