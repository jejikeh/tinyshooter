// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShooterPlayerController.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    SetInputMode(FInputModeGameOnly());
}
