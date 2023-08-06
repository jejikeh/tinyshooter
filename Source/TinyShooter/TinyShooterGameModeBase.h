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
    
    // this better to store in FGameData Struct
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int32 CurrentRound = 0;
    
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    float CurrentRoundTime = 0;

    // TODO: move to private property and implement getters and setters
    int32 CurrentLivePlayers = 0;

protected:
    EGameState CurrentRoundState = EGameState::NotStarted;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

    FTimerHandle RoundTimerHandle;
    
    void StartRound();
    void RoundTimerUpdate();

    void ResetPlayers();
    void ResetPlayer(AController* Player);

    void FinishGame();

    void SetGameState(EGameState State);
    virtual void GenericPlayerInitialization(AController* C) override;

    bool bGameWasStarted;
};
