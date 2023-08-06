// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShooterPlayerController.h"
#include "TinyShooterGameState.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    SetInputMode(FInputModeGameOnly());
}

void AShooterPlayerController::Client_OnGameStateChanged_Implementation(EGameState State)
{
    ATinyShooterGameState* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<ATinyShooterGameState>() : NULL;

    if (MyGameState)
    {
        MyGameState->GameStateChanged(State);
    }
}