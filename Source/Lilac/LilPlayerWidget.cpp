// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayerWidget.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/GridSlot.h"
#include "SlateCore/Public/Styling/SlateColor.h"

void ULilPlayerWidget::UpdateTextBlocks(const TArray<ALilBaseCharacter*>& DetectedActors)
{
	DetectedActors_Panel->ClearChildren();

	for (int32 Index = 0; Index < DetectedActors.Num(); Index++)
	{
		AddTextBlock(DetectedActors[Index], Index);
	}
}

void ULilPlayerWidget::AddTextBlock(AActor* Actor, int32 Index)
{
    if (!Actor) return;

    UTextBlock* TextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
    TextBlock->SetText(FText::FromString(Actor->GetName()));

   //FSlateColor TextColor = FSlateColor(FLinearColor::Black);
    TextBlock->SetShadowColorAndOpacity(FLinearColor::Black);
    int32 Row = Index / 2;
    int32 Column = Index % 2;
    UGridSlot* GridSlot = DetectedActors_Panel->AddChildToGrid(TextBlock, Row, Column);
    if (GridSlot)
    {
        GridSlot->SetPadding(FMargin(5.0f));
    }
}
