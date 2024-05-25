// Fill out your copyright notice in the Description page of Project Settings.


#include "LilPlayer.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ALilPlayer::ALilPlayer()
{
	PriorityID = FPriorityID(1, "Player");
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
	
	//탐지범위
	if (IsValid(this) && this->GetWorld())
	{
		SphereComponent = NewObject<USphereComponent>(this);
		SphereComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		SphereComponent->SetWorldLocation(this->GetActorLocation());
		SphereComponent->InitSphereRadius(5000.0f);
		SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 채널 무시
		SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
		SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap); //Enemy로 설정된 채널만 Overlap검사
		SphereComponent->RegisterComponent();
	
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALilPlayer::OnDetected);
		SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ALilPlayer::OnLost);
	}

	//탐지액터 map생성
	Initialize_PriorityMap();

	UAnimInstance* pAnimInstance = GetMesh()->GetAnimInstance();
	if (pAnimInstance)
	{
		pAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ALilPlayer::HandleOnMontageNotifyBegin);
	}
	comboIndex = 0;

	//StateManager = NewObject<UPlayerStateMachine>();
	//StateManager->player = this;
	//StateManager->ChangeState(UPlayerSearchState::StaticClass());

	//isAutoMode = false;

	R_Weapon = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("RightBlade")));
	L_Weapon = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("LeftBlade")));
	//DrawDebugSphere(GetWorld(), this->GetActorLocation(), 500.0f, 32, FColor::Red, false, 10.0f, 0, 1.0f);
}

void ALilPlayer::MoveInput(const FInputActionValue& Value)
{
	if (!isAttacking())
	{
		const FVector2D MoveVector = Value.Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MoveVector.Y);
		const FVector RightDriection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDriection, MoveVector.X);
		isAutoMode = false;
	}
}

void ALilPlayer::LookInput(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

//void ALilPlayer::AutoInput(const FInputActionValue& Value)
//{
//	if (isAutoMode)
//	{
//		UE_LOG(LogTemp, Log, TEXT("AutoMdoe OFF"));
//		StateManager->ChangeState(UPlayerSearchState::StaticClass());
//		isAutoMode = false;
//	}
//	else
//	{
//		UE_LOG(LogTemp, Log, TEXT("AutoMdoe ON"));
//		isAutoMode = true;
//	}
//}

void ALilPlayer::AttackInput(const FInputActionValue& Value)
{
	Attack();
}

void ALilPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (isAutoMode)
	//{
	//	StateManager->Update(DeltaTime);
	//}
}

void ALilPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALilPlayer::MoveInput);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALilPlayer::LookInput);
	//	EnhancedInputComponent->BindAction(AutoAction, ETriggerEvent::Triggered, this, &ALilPlayer::AutoInput);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ALilPlayer::AttackInput);
	}
}

void ALilPlayer::Attack()
{
	Super::Attack();

	//attack 구현
	if (!isAttacking())
	{
		UAnimInstance* animInst = GetMesh()->GetAnimInstance();
		if (animInst)
		{
			if (comboAttackMontage)
			{
				animInst->Montage_Play(comboAttackMontage);
			}
		}
	}
	else
	{
		comboIndex = 1;
	}
}
	
void ALilPlayer::HandleOnMontageNotifyBegin(FName notifyName, const FBranchingPointNotifyPayload& branchingPayload)
{
	comboIndex--;
	if (comboIndex < 0)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if (animInstance)
		{
			animInstance->Montage_Stop(0.3f, comboAttackMontage);
		}
	}
}

AActor* ALilPlayer::GetTarget()
{
	AActor* BestTarget = nullptr;
	float ClosestDistance = FLT_MAX;

	for (const auto& Elem : priorityMap)
	{
		for (AActor* Actor : Elem.Value)
		{
			float Distance = FVector::Dist(Actor->GetActorLocation(), GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				BestTarget = Actor;
			}
		}
		if (BestTarget)
		{
			break;
		}
	}

	return BestTarget;
}

void ALilPlayer::GetDetectedActors(TArray<ALilBaseCharacter*> &Array)
{
	Array = detectedActors;
}

void ALilPlayer::Initialize_PriorityMap()
{
	priorityMap.Add(1, TArray<AActor*>());
	priorityMap.Add(2, TArray<AActor*>());
	priorityMap.Add(3, TArray<AActor*>());
}

void ALilPlayer::AddToPriorityMap(AActor* Actor, int32 Priority)
{
	if (priorityMap.Contains(Priority))
	{
		priorityMap[Priority].Add(Actor);

	}
}

void ALilPlayer::RemoveFromPriorityMap(AActor* Actor, int32 Priority)
{
	if (priorityMap.Contains(Priority))
	{
		priorityMap[Priority].Remove(Actor);
	}
}

void ALilPlayer::SortDetectedActors()
{
	detectedActors.Sort([this](const ALilBaseCharacter& A, const ALilBaseCharacter& B)
		{			
			if (A.PriorityID.Priority == B.PriorityID.Priority)
			{
				return FVector::Dist(this->GetActorLocation(), A.GetActorLocation()) < FVector::Dist(this->GetActorLocation(), B.GetActorLocation());
			}
			return A.PriorityID.Priority > B.PriorityID.Priority;
		}
	);

	if (detectedActors.Num() > 8)
	{
		detectedActors.SetNum(8);
	}
}

void ALilPlayer::OnDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ALilBaseCharacter* BaseCharacter = Cast<ALilBaseCharacter>(OtherActor);
		if (BaseCharacter)
		{
			int32 priority = BaseCharacter->PriorityID.Priority;
			AddToPriorityMap(OtherActor, priority);
			detectedActors.AddUnique(BaseCharacter);
			UE_LOG(LogTemp, Log, TEXT("add"));
		}
	}
}

void ALilPlayer::OnLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ALilBaseCharacter* Basecharacter = Cast<ALilBaseCharacter>(OtherActor);		
		if (Basecharacter)
		{
			int32 priority = Basecharacter->PriorityID.Priority;
			RemoveFromPriorityMap(OtherActor, priority);
			detectedActors.Remove(Basecharacter);
			UE_LOG(LogTemp, Log, TEXT("remove"));
		}
	}
}


bool ALilPlayer::isAttacking()
{
	UAnimInstance* animInst = GetMesh()->GetAnimInstance();
	if (animInst)
	{
		if (animInst->Montage_IsPlaying(comboAttackMontage))
		{
			return true;
		}
	}
	return false;
}
