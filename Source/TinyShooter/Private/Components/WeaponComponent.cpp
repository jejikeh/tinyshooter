// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon(0);
}

void UWeaponComponent::StartShoot()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->StartShoot();
    }


    for (auto Weapon : Weapons)
    {
        if (Weapon)
        {
            Weapon->StartShoot();
        }
    }
}

void UWeaponComponent::StopShoot()
{   
    if (CurrentWeapon)
    {
        CurrentWeapon->StopShoot();
    }

    for (const auto Weapon : Weapons)
    {
        if (Weapon)
        {
            Weapon->StopShoot();
        }
    }
}

void UWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % WeaponClasses.Num();
    SpawnWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::SpawnWeapon(int32 WeaponIndex)
{

    if (auto const Character = Cast<ACharacter>(GetOwner()))
    {
        if (CurrentWeapon) 
        {
            CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            Weapons.Add(CurrentWeapon);
            
            AActor* CurrentWeaponActor = Cast<AActor>(CurrentWeapon);
            CurrentWeaponActor->Destroy();
            CurrentWeapon = nullptr;
        }

        if (const auto SpawnWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClasses[WeaponIndex]))
        {
            const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); 
            SpawnWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
            SpawnWeapon->SetOwner(Character);

            CurrentWeapon = SpawnWeapon;
        }
    }
}