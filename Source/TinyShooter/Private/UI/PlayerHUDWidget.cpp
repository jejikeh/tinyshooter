// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"

#include "Components/WeaponComponent.h"
#include "Player/BaseCharacter.h"

float UPlayerHUDWidget::GetHealthPercentage() const
{
    const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
    
    if (!Player)
    {
        return 0.0f;
    }

    return Player->HealthFromComponent;
}

bool UPlayerHUDWidget::GetWeaponUIData(FUIWeaponData &WeaponUIData) const
{
    const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
    
    if (!Player)
    {
        return false;
    }

    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);

    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->GetWeaponUIData(WeaponUIData);
}

bool UPlayerHUDWidget::GetWeaponAmmoData(FAmmoData &AmmoData) const
{
    const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());

    if (!Player)    
    {
        return false;
    }

    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);

    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->GetCurrentAmmoData(AmmoData);
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
    const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
    
    if (!Player)
    {
        return false;
    }

    return !Player->bIsDead;
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Player = GetOwningPlayer();
    
    if (!Player)
    {
        return false;
    }

    return Player->GetStateName() == NAME_Spectating;
}
