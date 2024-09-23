// Copyright Epic Games, Inc. All Rights Reserved.

#include "XyuanTestGameMode.h"
#include "XyuanTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AXyuanTestGameMode::AXyuanTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
