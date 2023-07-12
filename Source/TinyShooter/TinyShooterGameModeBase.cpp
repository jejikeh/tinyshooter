// Copyright Epic Games, Inc. All Rights Reserved.


#include "TinyShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/ShooterPlayerController.h"

ATinyShooterGameModeBase::ATinyShooterGameModeBase()
{
    // Overriding default pawn and controller class to ours
    DefaultPawnClass = ABaseCharacter::StaticClass();
    PlayerControllerClass = AShooterPlayerController::StaticClass();
}

void ATinyShooterGameModeBase::BeginPlay()
{
}
