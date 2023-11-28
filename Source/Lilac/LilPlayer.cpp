// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayer.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ALilPlayer::ALilPlayer()
{
}

void ALilPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	searchState = NewObject<UPlayerSearchState>();
	StateManager = NewObject<UPlayerStateMachine>();
	StateManager->CurrentState = searchState;
	StateManager->player = this;

	if (IsValid(this) && this->GetWorld())
	{
		SphereComponent = NewObject<USphereComponent>(this);
		SphereComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		SphereComponent->SetWorldLocation(this->GetActorLocation());
		SphereComponent->InitSphereRadius(1000.0f);
		SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 채널 무시
		SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap); //Enemy로 설정된 채널만 Overlap검사
		SphereComponent->RegisterComponent();
	}
	//DrawDebugSphere(GetWorld(), this->GetActorLocation(), 500.0f, 32, FColor::Red, false, 10.0f, 0, 1.0f);
}

void ALilPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MoveVector.Y);
	const FVector RightDriection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDriection, MoveVector.X);

}

void ALilPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ALilPlayer::Tick(float DeltaTime)
{
	StateManager->Update(DeltaTime);
}

void ALilPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALilPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALilPlayer::Look);
	}
}
