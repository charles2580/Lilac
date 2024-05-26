// Fill out your copyright notice in the Description page of Project Settings.


#include "LilBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALilBaseCharacter::ALilBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALilBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALilBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALilBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALilBaseCharacter::ChangeSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ALilBaseCharacter::Attack()
{
}
