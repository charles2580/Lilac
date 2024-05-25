// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayerWidget.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/GridSlot.h"
#include "Components/SizeBox.h"
#include "Engine/Texture2D.h"
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

    UBorder* Border = NewObject<UBorder>(this, UBorder::StaticClass());
    //FVector2D BorderSize(1.0f, 2.0f);
    //Border->SetDesiredSizeScale(BorderSize);
    
    UTextBlock* TextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
    TextBlock->SetText(FText::FromString(Actor->GetName()));
    TextBlock->SetColorAndOpacity(FLinearColor::Black);
    TextBlock->SetJustification(ETextJustify::Center);
    Border->SetContent(TextBlock);

    int32 Row = Index / 2;
    int32 Column = Index % 2;
    UGridSlot* GridSlot = DetectedActors_Panel->AddChildToGrid(Border, Row, Column);
    if (GridSlot)
    {
        GridSlot->SetPadding(FMargin(5.0f));
    }
}
