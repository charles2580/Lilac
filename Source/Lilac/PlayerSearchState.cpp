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

	//SphereCollider Ȯ�ο� ����׽����
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
	sphereCollider->SetCollisionResponseToAllChannels(ECR_Ignore); // ��� ä�� ����
	sphereCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap); //Enemy�� ������ ä�θ� Overlap�˻�

	TArray<AActor*> OverlappedActors;
	//Overlap �� ��� ���͵� �� LilEnemyŬ������ ��ȯ
	sphereCollider->GetOverlappingActors(OverlappedActors, ALilEnemy::StaticClass()); // AEnemy�� �� ĳ���� Ŭ����
	for (AActor* Actor : OverlappedActors) {
		float Distance = (Actor->GetActorLocation() - playerLocation).Size(); //�÷��̾�� �� ĳ������ �Ÿ� ���
		if (Distance < shortDistance) {
			shortDistance = Distance;
			targetActor = Actor;
			//UE_LOG(LogTemp, Log, TEXT("%s"), *TargetActor->GetName());
		}
	}
	return targetActor;
}
