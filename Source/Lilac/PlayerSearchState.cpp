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

	//SphereCollider 확인용 디버그스페어
	//DrawDebugSphere(newActor->GetWorld(), playerLocation, 1000.0f, 32, FColor::Red, false, 10.0f, 0, 1.0f);
	
	if (SearchTarget(newActor))// 타겟이 있으면 적오브젝트로 설정 -> MoveState로 변경
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
	//Overlap 된 모든 액터들 중 LilEnemy클래스만 반환
	sphereCollider->GetOverlappingActors(OverlappedActors, ALilEnemy::StaticClass()); // AEnemy는 적 캐릭터 클래스
	for (AActor* Actor : OverlappedActors) {
		float Distance = (Actor->GetActorLocation() - playerLocation).Size(); //플레이어와 적 캐릭터의 거리 계산
		if (Distance < shortDistance) {
			shortDistance = Distance;
			targetActor = Actor;
			//UE_LOG(LogTemp, Log, TEXT("%s"), *targetActor->GetName());
		}
	}
	return targetActor;
}
