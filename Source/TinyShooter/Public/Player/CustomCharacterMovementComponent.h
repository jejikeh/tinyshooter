// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API UCustomCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float RunSpeedMultiplier = 2.0f;
    
    virtual float GetMaxSpeed() const override;
};
