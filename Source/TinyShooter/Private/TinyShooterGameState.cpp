// Fill out your copyright notice in the Description page of Project Settings.


#include "TinyShooterGameState.h"

#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"
#include "TinyShooter/TinyShooterGameModeBase.h"

void ATinyShooterGameState::BeginPlay()
{
    Super::BeginPlay();

    if (const auto GameMode = Cast<ATinyShooterGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ATinyShooterGameState::GameStateChanged);
    }
}

void ATinyShooterGameState::GameStateChanged(EGameState State)
{
    CurrentRoundState = State;
    OnGameStateChanged.Broadcast(State);
}
