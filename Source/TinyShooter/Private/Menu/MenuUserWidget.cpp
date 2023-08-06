// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuUserWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UMenuUserWidget::StartGame()
{
    const FName StartLevelName = FName("L_Level");
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));
    UGameplayStatics::OpenLevel(this, StartLevelName);
}
