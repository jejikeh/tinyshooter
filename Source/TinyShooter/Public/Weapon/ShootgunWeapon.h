// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "ShootgunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API AShootgunWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
    virtual void StartShoot() override;
    virtual void MakeShootEffect() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
    float BulletsSpreadAmmount = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
    int32 BulletsCount = 3;
};
