// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

UCLASS()
class TINYSHOOTER_API AShooterPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(Client, Reliable)
    void Client_OnGameStateChanged(EGameState State);
    void Client_OnGameStateChanged_Implementation(EGameState State);

protected:
    virtual void BeginPlay() override;

};
