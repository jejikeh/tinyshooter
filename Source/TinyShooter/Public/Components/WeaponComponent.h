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
    TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
    FName WeaponAttachPointName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* ShootAnimation;

    void StartShoot();
    void StopShoot();
    void NextWeapon();
    void PlayWeaponAnimation();
    void PlayShootAnimation();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ABaseWeapon* CurrentWeapon = nullptr;

    int32 CurrentWeaponIndex = 0;

    void SpawnWeapon(int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* Animation);
};
