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
}

void UWeaponComponent::StartShoot()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->StartShoot();
        PlayShootAnimation();
    }
}

void UWeaponComponent::StopShoot()
{   
    if (CurrentWeapon)
    {
        CurrentWeapon->StopShoot();
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
        if (WeaponIndex < 0 || WeaponIndex >= WeaponClasses.Num())
        {
            WeaponIndex = 0;
        }
        
        if (CurrentWeapon) 
        {
            CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            CurrentWeapon->Destroy();
            CurrentWeapon = nullptr;
        }
        
        if (const auto SpawnWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClasses[WeaponIndex]))
        {
            const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); 
            SpawnWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
            SpawnWeapon->SetOwner(Character);
            CurrentWeapon = SpawnWeapon;
            PlayWeaponAnimation();
        }
    }
}

void UWeaponComponent::PlayWeaponAnimation()
{
    PlayAnimMontage(EquipAnimMontage);
}

void UWeaponComponent::PlayShootAnimation()
{
    PlayAnimMontage(ShootAnimation);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    const auto Character = Cast<ACharacter>(GetOwner());

    if (!Character)
    {
        return;
    }

    Character->PlayAnimMontage(Animation);
}
