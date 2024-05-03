// Fill out your copyright notice in the Description page of Project Settings.


#include "LilNS_Hellfire.h"
#include "TimerManager.h"

void ULilNS_Hellfire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AActor* boss = MeshComp->GetOwner())
	{
		FVector bossLoc = boss->GetActorLocation();
		bossLoc.Z = 102.0f;
		FRotator spawnRot(0.0f, 0.0f, 0.0f);
		FVector spawnLoc = boss->GetActorForwardVector() * 500.0f * SpawnIndex + bossLoc;
		FVector spawnSize(2.0f, 2.0f, 2.0f);
		attackArea = boss->GetWorld()->SpawnActor<AActor>(ActorToSpawn, spawnLoc, spawnRot);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(boss->GetWorld(), ExplosiveEffect, spawnLoc,spawnRot,spawnSize);
	}
	
}

void ULilNS_Hellfire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	attackArea = nullptr;
}

