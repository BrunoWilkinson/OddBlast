// Copyright Epic Games, Inc. All Rights Reserved.

#include "OddBlastGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "../Characters/PlayerCharacter.h"

AOddBlastGameMode::AOddBlastGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Core/Character/Player/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AOddBlastGameMode::EndGame(bool bIsPlayerWinner)
{}
