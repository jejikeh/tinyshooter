// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/BaseWeapon.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercentage() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FUIWeaponData &WeaponUIData) const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FAmmoData &AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;
};
