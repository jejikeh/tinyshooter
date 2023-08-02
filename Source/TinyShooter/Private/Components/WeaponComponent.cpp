// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

bool UWeaponComponent::GetCurrentAmmoData(FAmmoData &AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetCurrentAmmoData();
        
        return true;
    }
    
    return false;
}

bool UWeaponComponent::GetWeaponUIData(FUIWeaponData &WeaponUIData) const
{
    if (CurrentWeapon)
    {
        WeaponUIData = CurrentWeapon->GetWeaponUIData();
        
        return true;
    }
    
    return false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UWeaponComponent::BeginDestroy()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        CurrentWeapon->SetLifeSpan(1.0f);
        
        CurrentWeapon = nullptr;
        CurrentReloadAnimMontage = nullptr;
        CurrentShootAnimMontage = nullptr;
    }
    
    Super::BeginDestroy();
}

void UWeaponComponent::StartShoot()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->StartShoot();
        PlayShootAnimation();
    }
}

void UWeaponComponent::StopShoot() const
{   
    if (CurrentWeapon)
    {
        CurrentWeapon->StopShoot();
    }
}

/**
 * @brief Spawns the next weapon on the server and plays the weapon equip animation
 */
void UWeaponComponent::Server_NextWeapon()
{
    Server_SpawnWeapon(CurrentWeaponIndex);
}

/**
 * @brief Set animation references for the next weapon and Play weapon equip animation. Used in Multicast call
 */
void UWeaponComponent::SetNextWeaponAnimRefs()
{
    if (WeaponData.IsEmpty())
    {
        return;
    }
    
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % WeaponData.Num();
    const auto CurrentWeaponData = WeaponData[CurrentWeaponIndex];
    SetAnimMontageReference(CurrentWeaponData);
}

/**
 * @brief This function sets reference to WeaponData. This used in Server and Client to keep track of the current weapon and his animations
 * @param CurrentWeaponData Element in Array of WeaponData, passed from Server_SpawnWeapon
 */
 void UWeaponComponent::SetAnimMontageReference(const TArray<FWeaponData>::ElementType &CurrentWeaponData)
{
    CurrentShootAnimMontage = CurrentWeaponData.ShootAnimMontage;
    CurrentReloadAnimMontage = CurrentWeaponData.ReloadAnimMontage;
}

void UWeaponComponent::Reload()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Reload();
        PlayReloadAnimation();
    }
}

void UWeaponComponent::Server_SpawnWeapon(int32 WeaponIndex)
{
    if (WeaponData.IsEmpty())
    {
        return;
    }
    
    if (auto const Character = Cast<ACharacter>(GetOwner()))
    {
        if (WeaponIndex < 0 || WeaponIndex >= WeaponData.Num())
        {
            WeaponIndex = 0;
        }
        
        if (CurrentWeapon) 
        {
            CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            CurrentWeapon->Destroy();

            CurrentWeapon = nullptr;
            CurrentReloadAnimMontage = nullptr;
            CurrentShootAnimMontage = nullptr;
        }

        const auto CurrentWeaponData = WeaponData[WeaponIndex];
        
        if (const auto SpawnWeapon = GetWorld()->SpawnActor<ABaseWeapon>(CurrentWeaponData.WeaponClass))
        {
            const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); 
            SpawnWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
            SpawnWeapon->SetOwner(Character);
            CurrentWeapon = SpawnWeapon;

            // This is doesn't work because the weapon is not spawned yet, and SpawnWeapon will be nullptr
            /*
            if (Character->HasAuthority())
            {
                // this sets the current weapon ref to owner actor component. This is bc the weapon spawned by the server
                Client_SetCurrentWeaponRef(CurrentWeapon);
            }
            */
        }
    }
}

void UWeaponComponent::PlayWeaponEquipAnimation() const
{
    PlayAnimMontage(EquipAnimMontage); 
}

void UWeaponComponent::PlayShootAnimation()
{
    if (!CurrentShootAnimMontage) {
        SetAnimMontageReference(WeaponData[CurrentWeaponIndex]);
    }
    
    PlayAnimMontage(CurrentShootAnimMontage);
}

void UWeaponComponent::PlayReloadAnimation()
{
    if (!CurrentReloadAnimMontage) {
        SetAnimMontageReference(WeaponData[CurrentWeaponIndex]);
    }
    
    PlayAnimMontage(CurrentReloadAnimMontage);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
    const auto Character = Cast<ACharacter>(GetOwner());

    if (!Character)
    {
        return;
    }

    Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UWeaponComponent, CurrentWeapon);
}
