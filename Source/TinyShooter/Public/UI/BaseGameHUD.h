// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API ABaseGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrosshair();
	
};
