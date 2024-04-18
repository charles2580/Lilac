// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "LilNS_ExplosiveAttack.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ULilNS_ExplosiveAttack : public UAnimNotifyState
{
	GENERATED_BODY()


public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		const FAnimNotifyEventReference& EventReference);

	UPROPERTY(EditAnyWhere)
	TSubclassOf<AActor>ActorToSpawn;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ExplosiveEffect;

private:
	FVector spawnLoc;
	AActor* attackArea;
};
