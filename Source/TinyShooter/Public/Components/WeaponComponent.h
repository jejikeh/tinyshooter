// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINYSHOOTER_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public: 
    // Sets default values for this component's properties
    UWeaponComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
    FName WeaponAttachPointName = "WeaponSocket";

    void Shoot();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ABaseWeapon* CurrentWeapon = nullptr;

    void SpawnWeapon();
};
