// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LilBaseCharacter.h"
#include "LilPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class LILAC_API ULilPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerWidget", meta =(BindWidget))
	class UGridPanel* DetectedActors_Panel;

	void UpdateTextBlocks(const TArray<ALilBaseCharacter*>& DetectedActors);

private:
	void AddTextBlock(AActor* Actor, int32 Index);
};
