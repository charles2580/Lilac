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

//	autoMode Ű �Է¿� ���� AI Controller�� Player Controller�� ����.
//	Controller->Possess()�� ȣ���ϸ� �Լ������� ������ ����� Controller�� Unpossess�ϱ� ������ ���� UnPossess()ȣ�� �ʿ�X
void ALilPlayerController::ToggleAutoMode()
{
	if (LilPlayer)
	{
		if (!isAutoMode)
		{
			AIC_Player->Possess(LilPlayer);
			
			//SetPawn(LilPlayer);  PlayerController�� ���ǵ� pawn�� null�� �Ǿ��� ������ pawn�� �缳��
			//SetViewTarget(LilPlayer); viewTarget ���� �缳��, --> ������ ������, ī�޶��� �������� �ε巴�� ����.
			isAutoMode = true;
			return;
		}
		Possess(LilPlayer);
		isAutoMode = false;
	}
}