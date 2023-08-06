// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon/BulletProjectile.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class USoundCue;
class ABulletProjectile;

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    int32 Ammo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!bInfinite"))
    int32 Clips;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    bool bInfinite;
};

USTRUCT(BlueprintType)
struct FUIWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};

UCLASS()
class TINYSHOOTER_API ABaseWeapon : public AItem
{
    GENERATED_BODY()
    
public: 
    ABaseWeapon();

    virtual void StartShoot();
    virtual void StopShoot();
    virtual void MakeShootEffect();
    void Reload();
    void DecreaseCurrentAmmo();
    FAmmoData GetCurrentAmmoData() const;
    FUIWeaponData GetWeaponUIData() const;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float TraceMaxDistance = 1000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
    TSubclassOf<ABulletProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
    FAmmoData DefaultAmmo;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "UI")
    FUIWeaponData WeaponUIData;

    // UFUNCTION()
    // void OnPlayerDestroyed(AActor * DestroyedActor);
    virtual void BeginPlay() override;
    void ApplyDamage(const FHitResult& HitResult);
    AController* GetPlayerController() const;

    virtual void SpawnBulletProjectile(const FVector& Direction);
    virtual FTransform GetMuzzleTransform();
    virtual void GetPlayerViewPoint(FVector& Location, FRotator& Rotation);

    bool IsCurrentAmmoEmpty() const;
    bool IsReloadRequired() const;
    void LogAmmo() const;

private:
    UPROPERTY(Replicated)
    FAmmoData CurrentAmmo;
};
