// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LilBaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerSearchState.h"
#include "Components/SphereComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		UAnimMontage* MyAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Direction;

protected:

	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* AutoAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* AttackAction;

	void MoveInput(const FInputActionValue& Value);
	void LookInput(const FInputActionValue& Value);
	void AutoInput(const FInputActionValue& Value);
	void AttackInput(const FInputActionValue& Value);

private:
	UObject* searchState = nullptr;
	bool isAutoMode;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();

};