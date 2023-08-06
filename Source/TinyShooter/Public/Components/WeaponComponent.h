// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/BaseWeapon.h"
#include "WeaponComponent.generated.h"

struct FUIWeaponData;
struct FAmmoData;
class USoundCue;
class ABaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Animation")
    UAnimMontage* ReloadAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* ShootAnimMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
    USoundCue* FireSound;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINYSHOOTER_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public: 
    // Sets default values for this component's properties
    UWeaponComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
    FName WeaponAttachPointName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    UAnimMontage* EquipAnimMontage;
    
    bool GetCurrentAmmoData(FAmmoData& AmmoData) const;
    bool GetWeaponUIData(FUIWeaponData& WeaponUIData) const;
    
    void StartShoot();
    void StopShoot() const;
    void Server_NextWeapon();
    void SetAnimMontageReference(const TArray<FWeaponData>::ElementType &CurrentWeaponData);
    void SetNextWeaponAnimRefs();
    void Reload();
    void PlayWeaponEquipAnimation() const;
    void PlayShootAnimation();
    void PlayReloadAnimation();

    /*
    UFUNCTION(Client, Reliable)
    void Server_Multicast_DecreaseAmmo();
    void Server_Multicast_DecreaseAmmo_Implementation();
    */

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    virtual void BeginDestroy() override;

private:
    UPROPERTY(Replicated)
    ABaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    UPROPERTY()
    UAnimMontage* CurrentShootAnimMontage = nullptr;

    UPROPERTY()
    USoundCue* CurrentShootSound = nullptr;

    int32 CurrentWeaponIndex = 0;

    void Server_SpawnWeapon(int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* Animation) const;
};
