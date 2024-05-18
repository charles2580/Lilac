// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ALilPlayerController::ALilPlayerController()
{
	isAutoMode = false;
	LilPlayer = nullptr;
	AIC_Player = nullptr;
}

void ALilPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("ToggleAutoMode", IE_Pressed, this, &ALilPlayerController::ToggleAutoMode);
}

void ALilPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (AI_Controller && LilPlayer)
	{
		AIC_Player = GetWorld()->SpawnActor<AAIController>(AI_Controller, LilPlayer->GetActorLocation(), LilPlayer->GetActorRotation());
	}
}

void ALilPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isAutoMode)
	{
		SetViewTarget(LilPlayer);
	}
}

void ALilPlayerController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);
	LilPlayer = PawnToPossess;
}

//	autoMode 키 입력에 따라 AI Controller와 Player Controller를 변경.
//	Controller->Possess()를 호출하면 함수내에서 기존에 연결된 Controller를 Unpossess하기 때문에 따로 UnPossess()호출 필요X
void ALilPlayerController::ToggleAutoMode()
{
	if (LilPlayer)
	{
		if (!isAutoMode)
		{
			AIC_Player->Possess(LilPlayer);
			
			//SetPawn(LilPlayer);  PlayerController의 빙의된 pawn이 null이 되었기 때문에 pawn을 재설정
			//SetViewTarget(LilPlayer); viewTarget 또한 재설정, --> 동작은 하지만, 카메라의 움직임이 부드럽지 못함.
			isAutoMode = true;
			return;
		}
		Possess(LilPlayer);
		isAutoMode = false;
	}
}