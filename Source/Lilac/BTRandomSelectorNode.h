// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTRandomSelectorNode.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API UBTRandomSelectorNode : public UBTCompositeNode
{
	GENERATED_BODY()

	explicit UBTRandomSelectorNode(const FObjectInitializer& ObjectInitializer);

	virtual int32 GetNextChildHandler(FBehaviorTreeSearchData& SearchData,
		int32 PrevChild, EBTNodeResult::Type LastResult) const override;
};
