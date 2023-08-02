// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuHUD.h"

#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass))
    {
        MenuWidget->AddToViewport();
    }
}
