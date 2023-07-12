// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TinyShooterGameModeBase.generated.h"

UCLASS()
class TINYSHOOTER_API ATinyShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ATinyShooterGameModeBase();
    
    virtual void BeginPlay() override;

};
