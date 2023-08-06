// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseGameHUD.h"

#include "TinyShooterGameState.h"
#include "Blueprint/UserWidget.h"

void ABaseGameHUD::DrawHUD() 
{
	Super::DrawHUD();
}


void ABaseGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    GameStateWidgets.Add(
        EGameState::InProgress,
        CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));

    GameStateWidgets.Add(
        EGameState::Finished,
        CreateWidget<UUserWidget>(GetWorld(), GameFinishHUDWidgetClass));

    for (const auto& WidgetTuple : GameStateWidgets)
    {
        const auto Widget = WidgetTuple.Value;
        if (!Widget)
        {
            continue;
        }

        Widget->AddToViewport();
        Widget->SetVisibility(ESlateVisibility::Hidden);

        // this hack is used bc when new player connected, gamemode gets only player controller, while the ui is not initialze
        CurrentWidget = GameStateWidgets[EGameState::InProgress];
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    if (const auto GameState = Cast<ATinyShooterGameState>(GetWorld()->GetGameState()))
    {
        GameState->OnGameStateChanged.AddUObject(this, &ABaseGameHUD::OnGameStateChanged);
    }
}

/**
 * @brief This function is called when the game state changes on the all clients
 * @param State The new game state
 */
void ABaseGameHUD::OnGameStateChanged(EGameState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameStateWidgets.Contains(State))
    {
        CurrentWidget = GameStateWidgets[State];
    }
    
    CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    UE_LOG(LogTemp, Warning, TEXT("State: %s"), *UEnum::GetValueAsString(State));
}