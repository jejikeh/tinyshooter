// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CustomCharacterMovementComponent.h"

#include "Player/BaseCharacter.h"

float UCustomCharacterMovementComponent::GetMaxSpeed() const
{
    const auto MaxSpeed =  Super::GetMaxSpeed();

    if (const auto Player = Cast<ABaseCharacter>(GetPawnOwner()))
    {
        if (Player->IsRunning())
        {
            return MaxSpeed * RunSpeedMultiplier;
        }
    }
    
    return MaxSpeed;
}
