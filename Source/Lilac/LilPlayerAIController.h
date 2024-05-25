// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LilPlayer.h"
#include "LilPlayerWidget.h"
#include "LilPlayerAIController.generated.h"

/**
 * 
 */
class UBehaviorTreeComponent;
class UBlackboardComponent;


UCLASS()
class LILAC_API ALilPlayerAIController : public AAIController
{
	GENERATED_BODY()

public:

	explicit ALilPlayerAIController(FObjectInitializer const& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* APawn)override;
	virtual void OnUnPossess()override;
	void SetTarget();

private:

	FTimerHandle TimerHandle_UpdateTarget;	

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULilPlayerWidget> playerWidget;

	class UBlackboardComponent* blackboard;
	void UpdateDetectedActor();

	UFUNCTION()
	void OnTargetDestroyed(AActor* DestroyedActor);

	TArray<ALilBaseCharacter*> detectedActors;

	ULilPlayerWidget* gridWidget;
	float targetUpdate_Interval;
	AActor* target;

};
