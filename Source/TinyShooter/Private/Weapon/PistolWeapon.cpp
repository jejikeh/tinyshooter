// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PistolWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Controller.h"

void APistolWeapon::StartShoot()
{
    MakeShootEffect();
    GetWorldTimerManager().SetTimer(ShotTimerHandler, this, &ABaseWeapon::MakeShootEffect, ShootingDelay, true);
}

void APistolWeapon::StopShoot()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandler);
}

void APistolWeapon::MakeShootEffect()
{
    FVector TraceStart;
    FRotator ViewRotation;
    GetPlayerViewPoint(TraceStart, ViewRotation);

    const auto SocketTransform = GetMuzzleTransform();
    const auto HalfRad = FMath::DegreesToRadians(BulletsSpreadAmmount);
    const auto ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    const auto TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, SocketTransform.GetLocation(), TraceEnd, ECollisionChannel::ECC_Visibility);

    const auto EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const auto BulletDirection = (EndPoint - GetMuzzleTransform().GetLocation()).GetSafeNormal();

    SpawnBulletProjectile(BulletDirection);
}