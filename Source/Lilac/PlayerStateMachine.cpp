// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachine.h"

void UPlayerStateMachine::ChangeState(TSubclassOf<UObject> NewStateClass)
{
    if (NewStateClass != NULL)
    {
        if (CurrentState)
        {
            IBaseState* BaseStateInterface = Cast<IBaseState>(CurrentState);
            if (BaseStateInterface)
            {
                BaseStateInterface->OnExitState();
            }
            CurrentState->ConditionalBeginDestroy();//새로운 상태로 전환하기 전에 현재 상태의 리소스를 정리
        }

        CurrentState = NewObject<UObject>(this, NewStateClass);
        if (CurrentState)
        {
            IBaseState* BaseStateInterface = Cast<IBaseState>(CurrentState);
            if (BaseStateInterface)
            {
                BaseStateInterface->OnEnterState(player, deltaTime);
            }
        }
    }
}

void UPlayerStateMachine::Update(float DeltaTime)
{
    deltaTime = DeltaTime;
    if (CurrentState)
    {
        IBaseState* BaseStateInterface = Cast<IBaseState>(CurrentState);
        if (BaseStateInterface)
        {
            BaseStateInterface->UpdateState(player, deltaTime);
        }
    }
}

void UPlayerStateMachine::ExitState()
{
    IBaseState* BaseStateInterface = Cast<IBaseState>(CurrentState);
    if (BaseStateInterface)
    {
        BaseStateInterface->OnExitState();
    }
}
