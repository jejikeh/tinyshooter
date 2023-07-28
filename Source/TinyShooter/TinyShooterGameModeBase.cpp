// Copyright Epic Games, Inc. All Rights Reserved.


#include "TinyShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/ShooterPlayerController.h"
#include "UI/BaseGameHUD.h"

ATinyShooterGameModeBase::ATinyShooterGameModeBase()
{
    // Overriding default pawn and controller class to ours
    DefaultPawnClass = ABaseCharacter::StaticClass();
    PlayerControllerClass = AShooterPlayerController::StaticClass();
    HUDClass = ABaseGameHUD::StaticClass();
}
