// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Controller.h"

struct FDamageEvent;

ABaseWeapon::ABaseWeapon()
{
    bReplicates = true;
    PrimaryActorTick.bCanEverTick = false;
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseWeapon::StartShoot()
{
}

void ABaseWeapon::StopShoot()
{
}

AController* ABaseWeapon::GetPlayerController()
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


    ABulletProjectile* BulletProjectile = GetWorld()->SpawnActorDeferred<ABulletProjectile>(ProjectileClass, SpawnTransform);

    if (BulletProjectile)
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
    Controller->GetPlayerViewPoint(Location, Rotation);
}