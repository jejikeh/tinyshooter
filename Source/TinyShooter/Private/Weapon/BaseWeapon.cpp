// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Net/UnrealNetwork.h"

struct FDamageEvent;

ABaseWeapon::ABaseWeapon()
{
    bReplicates = true;
    PrimaryActorTick.bCanEverTick = false;
}

/*
void ABaseWeapon::OnPlayerDestroyed(AActor *DestroyedActor)
{
    Destroy();
}*/

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    
    CurrentAmmo = DefaultAmmo;
    /*
    if (const auto Player = Cast<ACharacter>(GetOwner())) 
    {
        Player->OnDestroyed.AddDynamic(this, &ABaseWeapon::OnPlayerDestroyed);
    } */
}

void ABaseWeapon::StartShoot()
{
}

void ABaseWeapon::StopShoot()
{
}

AController* ABaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) 
    {
        return nullptr;
    }

    return Player->GetController<APlayerController>();
}

void ABaseWeapon::MakeShootEffect()
{
}

void ABaseWeapon::ApplyDamage(const FHitResult& HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    
    if (!DamageActor)
    {
        return;
    }

    DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ABaseWeapon::SpawnBulletProjectile(const FVector& Direction)
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleTransform().GetLocation());
    UE_LOG(LogNet, Warning, TEXT("Client shoot"));

    if (ABulletProjectile* BulletProjectile = GetWorld()->SpawnActorDeferred<ABulletProjectile>(ProjectileClass, SpawnTransform))
    {
        BulletProjectile->SetShotDirection(Direction);
        BulletProjectile->SetDamageAmount(DamageAmount);
        BulletProjectile->FinishSpawning(SpawnTransform);
    }
}

FTransform ABaseWeapon::GetMuzzleTransform()
{
    return ItemMesh->GetSocketTransform(MuzzleSocketName);
}

void ABaseWeapon::GetPlayerViewPoint(FVector& Location, FRotator& Rotation)
{
    const auto Controller = GetPlayerController();

    if (!Controller)
    {
        return;
    }
    
    Controller->GetPlayerViewPoint(Location, Rotation);
}

void ABaseWeapon::DecreaseCurrentAmmo()
{
    CurrentAmmo.Ammo--;
    LogAmmo();
}

bool ABaseWeapon::IsCurrentAmmoEmpty() const
{
    return (CurrentAmmo.Clips == 0 || IsReloadRequired()) && !CurrentAmmo.bInfinite;
}

bool ABaseWeapon::IsReloadRequired() const
{
    return CurrentAmmo.Ammo <= 0;
}

void ABaseWeapon::Reload()
{
    CurrentAmmo.Ammo = DefaultAmmo.Ammo;
    if (!CurrentAmmo.bInfinite && CurrentAmmo.Clips > 0)
    {
        CurrentAmmo.Clips--;
    }
}

FAmmoData ABaseWeapon::GetCurrentAmmoData() const
{
    return CurrentAmmo;
}

FUIWeaponData ABaseWeapon::GetWeaponUIData() const
{
    return WeaponUIData;
}

void ABaseWeapon::LogAmmo() const
{
    const auto AmmoInformation = FString::Printf(
        TEXT("Ammo: %d Clips: %d Is Infinite: %s"),
        CurrentAmmo.Ammo,
        CurrentAmmo.Clips,
        CurrentAmmo.bInfinite ? TEXT("True") : TEXT("False"));

    UE_LOG(LogTemp, Warning, TEXT("%s"), *AmmoInformation);
}

void ABaseWeapon::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABaseWeapon, CurrentAmmo);
}