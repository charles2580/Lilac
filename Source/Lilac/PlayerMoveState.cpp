// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoveState.h"
#include "LilPlayer.h"

void UPlayerMoveState::OnEnterState(AActor* newActor, float deltaTime)
{
	player = Cast<ALilPlayer>(newActor);
	targetActor = Cast<ALilPlayer>(newActor)->Enemy;
	targetLocation = targetActor->GetActorLocation();
	stateManager = Cast<ALilPlayer>(newActor)->StateManager;
	moveSpeed = 300.0f;
	//animInstance = Cast<ALilPlayer>(newActor)->GetMesh()->GetAnimInstance();

	//UpdateState(newActor, deltaTime);
}

void UPlayerMoveState::UpdateState(AActor* newActor, float deltaTime) //적에게 이동하는 로직
{	
	FVector playerDirection = (targetLocation - player->GetActorLocation()).GetSafeNormal(); //플레이어의 새로운 방향벡터
	float distance = FVector::Dist(targetLocation, player->GetActorLocation()); //타겟과 플레이어 사이의 거리
	FRotator newDirection = playerDirection.Rotation();
	player->SetActorRotation(newDirection); //플레이어가 타겟을 바라보게 함

	if (!playerDirection.IsZero() && distance > 100.0f) //100.0f = 공격할수있는 최소한의 거리
	{
		FVector newLocation = player->GetActorLocation() + playerDirection * moveSpeed * deltaTime;
		FVector CalculatedVelocity = (newLocation - player->GetActorLocation()) / deltaTime;
		Cast<ALilPlayer>(newActor)->Speed = CalculatedVelocity;
		player->SetActorLocation(newLocation); //플레이어 위치 재설정
	}

	//if (AnimInstance)
	//{
	//	FVector Velocity = player->GetVelocity();
	//	float Speed = Velocity.Size();
	//	float Direction = AnimInstance->CalculateDirection(Velocity, player->GetActorRotation());

	//	/*AnimInstance->set
	//	AnimInstance->SetFloatParameter("Speed", Speed);
	//	AnimInstance->SetFloatParameter("Direction", Direction);*/
	//}

	if (distance < 150.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("is arrived"));
		stateManager->ChangeState(UPlayerAttackState::StaticClass());
	}
}

void UPlayerMoveState::OnExitState()
{
	targetActor = nullptr;
	targetLocation = FVector::ZeroVector;
	moveSpeed = 0.0f;
	player = nullptr;
	stateManager = nullptr;
}
