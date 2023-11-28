// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LilBaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerSearchState.h"
#include "PlayerMoveState.h"
#include "PlayerAttackState.h"
#include "BaseState.h"
#include "PlayerStateMachine.h"
#include "LilPlayer.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class LILAC_API ALilPlayer : public ALilBaseCharacter
{
	GENERATED_BODY()

public:
	ALilPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AActor* Enemy = nullptr;
	UPlayerStateMachine* StateManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USphereComponent* SphereComponent = nullptr;

protected:

	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* AutoAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	UObject* searchState = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};