// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LilBaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerSearchState.h"
#include "PlayerAttackState.h"
#include "PlayerMoveState.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
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

public:
	
	UPlayerStateMachine* StateManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Enemy = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		UAnimMontage* MyAnimMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")	
		UAnimMontage* comboAttackMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
		bool isAutoMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
		FVector Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
		UCapsuleComponent* R_Weapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
		UCapsuleComponent* L_Weapon;
protected:

	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* LookAction;

	//UPROPERTY(EditAnywhere, Category = Input)
	//	UInputAction* AutoAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* AttackAction;

private:
	//UObject* searchState = nullptr;
	float comboIndex;
	AActor* Target;
	TMap<int32, TArray<AActor*>> priorityMap;
	TArray<ALilBaseCharacter*> detectedActors;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void Attack() override;
	bool isAttacking();

	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName notifyName, const FBranchingPointNotifyPayload& branchingPayload);

	AActor* GetTarget();
	void GetDetectedActors(TArray<ALilBaseCharacter*> &Array);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveInput(const FInputActionValue& Value);
	void LookInput(const FInputActionValue& Value);
	//void AutoInput(const FInputActionValue& Value);
	void AttackInput(const FInputActionValue& Value);

private:

	void Initialize_PriorityMap();
	void AddToPriorityMap(AActor* Actor, int32 Priority);
	void RemoveFromPriorityMap(AActor* Actor, int32 Priority);
	void SortDetectedActors();

	UFUNCTION()
	void OnDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};