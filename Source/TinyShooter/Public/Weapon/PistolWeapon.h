// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "PistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API APistolWeapon : public ABaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartShoot() override;
    virtual void StopShoot() override;
    virtual void MakeShootEffect() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    float BulletsSpreadAmmount = 1.5f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    float ShootingDelay = 1.0f;

private:
    FTimerHandle ShotTimerHandler;
};
