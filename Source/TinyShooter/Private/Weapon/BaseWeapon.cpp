// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseWeapon::Shoot()
{
    UE_LOG(LogTemp, Display, TEXT("Shoot!"));
}