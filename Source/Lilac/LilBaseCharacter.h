// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LilBaseCharacter.generated.h"


USTRUCT(BlueprintType)
struct FPriorityID
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Priority")
    int32 Priority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Priority")
    FString ID;

    FPriorityID()
    {
        Priority = -1;
        ID = "None";
    }

    FPriorityID(int32 InPriority, FString InID)
    {
        Priority = InPriority;
        ID = InID;
    }
};


UCLASS()
class LILAC_API ALilBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALilBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ChangeSpeed(float speed);

	UFUNCTION()
	virtual void Attack();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Priority")
    FPriorityID PriorityID;
};
