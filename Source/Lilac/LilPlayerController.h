// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AIController.h"
#include "LilPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ALilPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	ALilPlayerController();

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AutoModeAction;

	UPROPERTY(EditAnyWhere, Category = AI)
	TSubclassOf<AAIController>AI_Controller;
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* PawnToPossess) override;
private:
	void ToggleAutoMode();
	bool isAutoMode;

	AAIController* AIC_Player;
	APawn* LilPlayer;
};
