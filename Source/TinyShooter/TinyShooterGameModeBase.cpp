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
    
    if (FMath::IsNearlyEqual(CurrentRoundTime, 0.0f) || CurrentLivePlayers < GetNumPlayers())
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

    // I know this is bad, but it is 2 am right now :)
    // It is better to do in the event "OnPlayerConnection" and cache the player.
    // But im not so into it right now 
    for (auto PlayerIterator = GetWorld()->GetControllerIterator(); PlayerIterator; ++PlayerIterator)
    {
        ABaseCharacter* Character = Cast<ABaseCharacter>(PlayerIterator->Get()->GetCharacter());
        if (Character)
        {
            Character->Client_SetRoundInfrormationToGameState(CurrentRoundTime, CurrentRound);
        }
    }
}

void ATinyShooterGameModeBase::ResetPlayers()
{
    for (auto PlayerIterator = GetWorld()->GetControllerIterator(); PlayerIterator; ++PlayerIterator)
    {
        ResetPlayer(PlayerIterator->Get());
    }

    CurrentLivePlayers = GetNumPlayers() + GetNumSpectators();
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

    // this is also bad. Here i defenetly could use TArray with Characters or controllers
    for (auto PlayerIterator = GetWorld()->GetControllerIterator(); PlayerIterator; ++PlayerIterator)
    {
        AShooterPlayerController* Controller = Cast<AShooterPlayerController>(PlayerIterator->Get());
        if (Controller)
        {
            Controller->Client_OnGameStateChanged(CurrentRoundState);
        }
    }
}

void ATinyShooterGameModeBase::GenericPlayerInitialization(AController* C)
{
    Super::GenericPlayerInitialization(C);

    AShooterPlayerController* Controller = Cast<AShooterPlayerController>(C);
    if (Controller)
    {
        // this is doesnt wotk for ui, because ui will initialize later
        Controller->Client_OnGameStateChanged(CurrentRoundState);
    }

    CurrentLivePlayers = GetNumPlayers() + GetNumSpectators();

    CurrentRound = 1;
    ResetPlayers();
    StartRound();
}