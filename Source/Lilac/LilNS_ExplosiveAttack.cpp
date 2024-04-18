// Fill out your copyright notice in the Description page of Project Settings.


#include "LilNS_ExplosiveAttack.h"
#include "LilPlayer.h"
#include "Kismet/GameplayStatics.h"

void ULilNS_ExplosiveAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AActor* boss = MeshComp->GetOwner())
	{
		FVector bossLoc = boss->GetActorLocation();
		bossLoc.Z = 102.0f;
		spawnLoc = bossLoc;
		FRotator spawnRot(0.0f, 0.0f, 0.0f);
		attackArea = boss->GetWorld()->SpawnActor<AActor>(ActorToSpawn, spawnLoc, spawnRot);
	}
}

void ULilNS_ExplosiveAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (attackArea)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), ExplosiveEffect, spawnLoc);
		
		if (ACharacter* player = UGameplayStatics::GetPlayerCharacter(MeshComp->GetWorld(), 0)) {
			TArray<AActor*> OverlappingActors;

			float whereplayer = (player->GetActorLocation() - attackArea->GetActorLocation()).Length();
			attackArea->GetOverlappingActors(OverlappingActors, ALilPlayer::StaticClass());
			if (OverlappingActors.Num() == 1 || 750.0f <= whereplayer && whereplayer <= 1000.0f)
			{
				UClass* DamageType = UDamageType::StaticClass();
				UGameplayStatics::ApplyDamage(OverlappingActors[0], 10.0f, attackArea->GetInstigatorController(), attackArea, DamageType);
			}

		}
		attackArea->Destroy();
	}
}
