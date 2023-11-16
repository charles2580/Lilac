// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LilBaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerSearchState.h"
#include "PlayerMoveState.h"
#include "PlayerAttackState.h"
#include "BaseState.h"
#include "LilPlayer.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class LILAC_API ALilPlayer : public ALilBaseCharacter
{
	GENERATED_BODY()

public:
	ALilPlayer();

private:
	IBaseState* currentState = nullptr;
	UObject* searchState = nullptr;
	UObject* moveState = nullptr;
	UObject* attackState = nullptr;

	//float t = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AActor* Enemy = nullptr;


protected:

	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};