// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoveState.h"
#include "LilPlayer.h"

void UPlayerMoveState::OnEnterState(AActor* newActor, float deltaTime)
{
	player = Cast<ALilPlayer>(newActor);
	targetActor = Cast<ALilPlayer>(newActor)->Enemy;
	targetLocation = targetActor->GetActorLocation();
	StateManager = Cast<ALilPlayer>(newActor)->StateManager;
	moveSpeed = 300.0f;
	//AnimInstance = Cast<ALilPlayer>(newActor)->GetMesh()->GetAnimInstance();

	isMoving = true;

	UpdateState(newActor, deltaTime);
}

void UPlayerMoveState::UpdateState(AActor* newActor, float deltaTime) //������ �̵��ϴ� ����
{
	if (!isMoving)
	{
		UE_LOG(LogTemp, Log, TEXT("is arrived"));
		//StateManager->ChangeState(UPlayerAttackState::StaticClass());
	}
	
	FVector playerDirection = (targetLocation - player->GetActorLocation()).GetSafeNormal(); //�÷��̾��� ���ο� ���⺤��
	float distance = FVector::Dist(targetLocation, player->GetActorLocation()); //Ÿ�ٰ� �÷��̾� ������ �Ÿ�
	FRotator newDirection = playerDirection.Rotation();
	player->SetActorRotation(newDirection); //�÷��̾ Ÿ���� �ٶ󺸰� ��
	if (!playerDirection.IsZero() && distance > 100.0f) //100.0f = �����Ҽ��ִ� �ּ����� �Ÿ�
	{
		FVector newLocation = player->GetActorLocation() + playerDirection * moveSpeed * deltaTime;
		player->SetActorLocation(newLocation); //�÷��̾� ��ġ �缳��
	}
	else
	{
		isMoving = false;
	}
}

void UPlayerMoveState::OnExitState()
{
	targetActor = nullptr;
	targetLocation = FVector::ZeroVector;
	moveSpeed = 0.0f;
	player = nullptr;
	StateManager = nullptr;
}
