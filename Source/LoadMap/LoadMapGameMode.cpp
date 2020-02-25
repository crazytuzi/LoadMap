// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LoadMapGameMode.h"
#include "LoadMapHUD.h"
#include "LoadMapCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALoadMapGameMode::ALoadMapGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALoadMapHUD::StaticClass();
}
