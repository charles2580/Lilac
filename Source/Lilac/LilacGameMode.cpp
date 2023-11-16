// Copyright Epic Games, Inc. All Rights Reserved.

#include "LilacGameMode.h"
#include "LilacCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALilacGameMode::ALilacGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
