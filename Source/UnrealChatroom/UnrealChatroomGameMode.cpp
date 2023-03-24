// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealChatroomGameMode.h"
#include "UnrealChatroomCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealChatroomGameMode::AUnrealChatroomGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
