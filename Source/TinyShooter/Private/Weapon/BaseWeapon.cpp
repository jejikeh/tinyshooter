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
    PrimaryActorTick.bCanEverTick = false;
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseWeapon::Shoot()
{
    UE_LOG(LogTemp, Display, TEXT("Shoot!"));
    MakeShootEffect();
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
    const auto Controller = GetPlayerController();

    FVector TraceStart;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(TraceStart, ViewRotation);

    const auto SocketTransform = ItemMesh->GetSocketTransform(MuzzleSocketName);
    const auto ShootDirection = ViewRotation.Vector();
    const auto TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, SocketTransform.GetLocation(), TraceEnd, ECollisionChannel::ECC_Visibility);

    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Yellow, false, 5.0f);

        ApplyDamage(HitResult);
    }
    else 
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }

    UGameplayStatics::PlaySound2D(this, FireSound);
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