// Copyright Epic Games, Inc. All Rights Reserved.

#include "MMOATGameMode.h"
#include "MMOATCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMMOATGameMode::AMMOATGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
