// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;
};
