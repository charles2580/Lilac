// Fill out your copyright notice in the Description page of Project Settings.


#include "BTRandomSelectorNode.h"

UBTRandomSelectorNode::UBTRandomSelectorNode(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "RandomSelector";
}

int32 UBTRandomSelectorNode::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{

	int32 NextChildIndex = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		NextChildIndex = FMath::RandRange(0, GetChildrenNum() - 1);
	}
	//else if (LastResult == EBTNodeResult::Succeeded)
	//{
	//	NextChildIndex = FMath::RandRange(0, GetChildrenNum() - 1);
	//}

	return NextChildIndex;
}
