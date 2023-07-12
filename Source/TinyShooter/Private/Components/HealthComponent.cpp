// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/FireDamageType.h"
#include "Dev/SteamDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    
    if (AActor* Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageEvent);
    }
}

float UHealthComponent::GetCurrentHealth()
{
    return Health;
}

bool UHealthComponent::IsDead()
{
    return FMath::IsNearlyZero(Health);
}

void UHealthComponent::OnTakeAnyDamageEvent(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser)
{
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

    OnHealthChangeEvent.Broadcast(Health, -Damage, DamageType);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
    {
        OnDeathEvent.Broadcast();
    }
    else if (bAutoHeal) 
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UHealthComponent::HealUpdate, HealTimeUpdate, true, StartHealDelay);
    }
}

void UHealthComponent::HealUpdate() 
{
    Health = FMath::Clamp(Health + HealModifier, 0.0f, MaxHealth);
    OnHealthChangeEvent.Broadcast(Health, HealModifier, nullptr);

    if (FMath::IsNearlyEqual(Health, MaxHealth))
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}