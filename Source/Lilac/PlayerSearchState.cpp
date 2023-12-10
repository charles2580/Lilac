// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSearchState.h"
#include "LilPlayer.h"
#include "DrawDebugHelpers.h"

void UPlayerSearchState::OnEnterState(AActor* newActor, float deltaTime)
{
	playerLocation = newActor->GetActorLocation();
	StateManager = Cast<ALilPlayer>(newActor)->StateManager;

	sphereCollider = Cast<ALilPlayer>(newActor)->SphereComponent;

	//UpdateState(newActor, deltaTime);
}

void UPlayerSearchState::UpdateState(AActor* newActor, float deltaTime)
{
	playerLocation = newActor->GetActorLocation();

	//SphereCollider Ȯ�ο� ����׽����
	//DrawDebugSphere(newActor->GetWorld(), playerLocation, 1000.0f, 32, FColor::Red, false, 10.0f, 0, 1.0f);
	
	if (SearchTarget(newActor))// Ÿ���� ������ ��������Ʈ�� ���� -> MoveState�� ����
	{
		Cast<ALilPlayer>(newActor)->Enemy = targetActor;
		StateManager->ChangeState(UPlayerMoveState::StaticClass());
	}
}

void UPlayerSearchState::OnExitState()
{
	targetActor = nullptr;
	playerLocation = FVector::ZeroVector;
	StateManager = nullptr;
}

AActor* UPlayerSearchState::SearchTarget(AActor* newActor)
{
	if (!newActor)
	{
		return nullptr;
	}

	playerLocation = newActor->GetActorLocation();
	float shortDistance = FLT_MAX;
	
	TArray<AActor*> OverlappedActors;
	//Overlap �� ��� ���͵� �� LilEnemyŬ������ ��ȯ
	sphereCollider->GetOverlappingActors(OverlappedActors, ALilEnemy::StaticClass()); // AEnemy�� �� ĳ���� Ŭ����
	for (AActor* Actor : OverlappedActors) {
		float Distance = (Actor->GetActorLocation() - playerLocation).Size(); //�÷��̾�� �� ĳ������ �Ÿ� ���
		if (Distance < shortDistance) {
			shortDistance = Distance;
			targetActor = Actor;
			//UE_LOG(LogTemp, Log, TEXT("%s"), *targetActor->GetName());
		}
	}
	return targetActor;
}
