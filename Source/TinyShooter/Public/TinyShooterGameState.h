// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TinyShooter/TinyShooterGameModeBase.h"
#include "TinyShooterGameState.generated.h"

UCLASS()
class TINYSHOOTER_API ATinyShooterGameState : public AGameState
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    FOnGameStateChangedSignature OnGameStateChanged;

    void GameStateChanged(EGameState State);

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int32 CurrentRound = 0;
    
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    float CurrentRoundTime = 0;

protected:
    EGameState CurrentRoundState = EGameState::NotStarted;
};
