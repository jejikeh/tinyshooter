// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseGameHUD.generated.h"

enum class EGameState : uint8;
/**
 * 
 */
UCLASS()
class TINYSHOOTER_API ABaseGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameFinishHUDWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<EGameState, UUserWidget*> GameStateWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;

    void OnGameStateChanged(EGameState State);
};
