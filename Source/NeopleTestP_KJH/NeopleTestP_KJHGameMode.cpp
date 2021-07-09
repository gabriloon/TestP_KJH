// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeopleTestP_KJHGameMode.h"
#include "NeopleTestP_KJHCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANeopleTestP_KJHGameMode::ANeopleTestP_KJHGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


