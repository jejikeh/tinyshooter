// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "TinyShooterGameModeBase.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8
{
    NotStarted,
    InProgress,
    Finished
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState);

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 PlayersCount = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 RoundsCount = 3;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    int32 RoundTimeInSeconds = 60;
};


UCLASS()
class TINYSHOOTER_API ATinyShooterGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
    ATinyShooterGameModeBase();

    virtual void StartPlay() override;

    FOnGameStateChangedSignature OnGameStateChanged;

protected:
    EGameState CurrentRoundState = EGameState::NotStarted;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

    int32 CurrentRound = 0;
    float CurrentRoundTime = 0;
    FTimerHandle RoundTimerHandle;
    
    void StartRound();
    void RoundTimerUpdate();

    void ResetPlayers();
    void ResetPlayer(AController* Player);

    void FinishGame();

    void SetGameState(EGameState State);
};
