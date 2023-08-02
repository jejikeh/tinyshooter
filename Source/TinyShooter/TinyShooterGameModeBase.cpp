// Copyright Epic Games, Inc. All Rights Reserved.


#include "TinyShooterGameModeBase.h"

#include "EngineUtils.h"
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

void ATinyShooterGameModeBase::StartPlay()
{
    Super::StartPlay();

    CurrentRound = 1;
    StartRound();

    SetGameState(EGameState::InProgress);
}

void ATinyShooterGameModeBase::StartRound()
{
    CurrentRoundTime = GameData.RoundTimeInSeconds;
    GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ATinyShooterGameModeBase::RoundTimerUpdate, 1.0f, true);
}

void ATinyShooterGameModeBase::RoundTimerUpdate()
{
    UE_LOG(LogTemp, Display, TEXT("------ ROUND %d ------ / TIME: %f"), CurrentRound, CurrentRoundTime);

    const auto TimerRate = GetWorldTimerManager().GetTimerRate(RoundTimerHandle);
    CurrentRoundTime -= TimerRate;
    
    if (FMath::IsNearlyEqual(CurrentRoundTime, 0.0f))
    {
        GetWorldTimerManager().ClearTimer(RoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsCount)
        {
            CurrentRound++;
            ResetPlayers();            
            StartRound();
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("------ GAME OVER  ------"));
            FinishGame();
        }
    }
}

void ATinyShooterGameModeBase::ResetPlayers()
{
    for (auto PlayerIterator = GetWorld()->GetControllerIterator(); PlayerIterator; ++PlayerIterator)
    {
        ResetPlayer(PlayerIterator->Get());
    }
}

void ATinyShooterGameModeBase::ResetPlayer(AController *Player)
{
    if (Player && Player->GetPawn())
    {
        Player->GetPawn()->Reset();
    }
    
    RestartPlayer(Player);
}

void ATinyShooterGameModeBase::FinishGame()
{
    for (const auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    SetGameState(EGameState::Finished);
}

void ATinyShooterGameModeBase::SetGameState(const EGameState State)
{
    // Get gamestate client
    CurrentRoundState = State;
    OnGameStateChanged.Broadcast(CurrentRoundState);
}
