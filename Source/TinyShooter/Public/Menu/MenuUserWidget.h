// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

class UButton;

UCLASS()
class TINYSHOOTER_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* HostGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* JoinGameButton;

    virtual void NativeOnInitialized() override;
    
private:
    void StartGame();
};
