// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSearchState.h"
#include "LilPlayer.h"
#include "DrawDebugHelpers.h"

void UPlayerSearchState::OnEnterState(AActor* newActor)
{
	playerLocation = newActor->GetActorLocation();
}

void UPlayerSearchState::UpdateState(AActor* newActor, float deltaTime)
{
	playerLocation = newActor->GetActorLocation();

	//SphereCollider 확인용 디버그스페어
	//DrawDebugSphere(newActor->GetWorld(), PlayerLocation, 500.0f, 32, FColor::Red, false, 10.0f, 0, 1.0f);
	Cast<ALilPlayer>(newActor)->Enemy = SearchTarget(newActor);
}

void UPlayerSearchState::OnExitState()
{
	sphereCollider->DestroyComponent();
	targetActor = nullptr;
	playerLocation = FVector::ZeroVector;
}

AActor* UPlayerSearchState::SearchTarget(AActor* newActor)
{
	if (!newActor)
	{
		return nullptr;
	}

	playerLocation = newActor->GetActorLocation();
	float shortDistance = FLT_MAX;
	sphereCollider = NewObject<USphereComponent>(newActor);
	sphereCollider->RegisterComponent();
	sphereCollider->SetWorldLocation(playerLocation);
	sphereCollider->InitSphereRadius(500.0f);
	sphereCollider->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 채널 무시
	sphereCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap); //Enemy로 설정된 채널만 Overlap검사

	TArray<AActor*> OverlappedActors;
	//Overlap 된 모든 액터들 중 LilEnemy클래스만 반환
	sphereCollider->GetOverlappingActors(OverlappedActors, ALilEnemy::StaticClass()); // AEnemy는 적 캐릭터 클래스
	for (AActor* Actor : OverlappedActors) {
		float Distance = (Actor->GetActorLocation() - playerLocation).Size(); //플레이어와 적 캐릭터의 거리 계산
		if (Distance < shortDistance) {
			shortDistance = Distance;
			targetActor = Actor;
			//UE_LOG(LogTemp, Log, TEXT("%s"), *TargetActor->GetName());
		}
	}
	return targetActor;
}
