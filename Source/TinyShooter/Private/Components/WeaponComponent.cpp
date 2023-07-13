// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void UWeaponComponent::Shoot()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Shoot();
    }
}

void UWeaponComponent::SpawnWeapon()
{
    if (auto const Character = Cast<ACharacter>(GetOwner()))
    {
        CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
        if (CurrentWeapon) 
        {
            const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); 
            CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
            CurrentWeapon->SetOwner(Character);
        }
    }
}