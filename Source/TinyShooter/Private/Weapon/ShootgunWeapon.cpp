// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ShootgunWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Controller.h"

void AShootgunWeapon::StartShoot()
{
    MakeShootEffect();
}

FVector ShiftVector(const FVector& InVector, float Shift)
{
    FVector RandomizedVector;
    RandomizedVector.X = FMath::RandRange(-Shift, Shift);
    RandomizedVector.Y = FMath::RandRange(-Shift, Shift);
    RandomizedVector.Z = FMath::RandRange(-Shift, Shift);

    return InVector + RandomizedVector;
}

void AShootgunWeapon::MakeShootEffect()
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

    UGameplayStatics::PlaySound2D(this, FireSound);

    const auto EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const auto BulletDirection = (EndPoint - GetMuzzleTransform().GetLocation()).GetSafeNormal();

    for (int i = 0; i < BulletsCount; ++i)
    {
        SpawnBulletProjectile(ShiftVector(BulletDirection, BulletsSpreadAmmount));
    }
}
