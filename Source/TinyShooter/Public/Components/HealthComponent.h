// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealthChange, float, float, const UDamageType*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINYSHOOTER_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
	// Sets default values for this component's properties
    UHealthComponent();

    UFUNCTION(BlueprintCallable)
    float GetCurrentHealth();

    UFUNCTION(BlueprintCallable)
    bool IsDead();
    
    UFUNCTION()
    void OnTakeAnyDamageEvent(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser );

    FOnDeath OnDeathEvent;
    FOnHealthChange OnHealthChangeEvent;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealHealth")
    bool bAutoHeal = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealHealth")
    float HealTimeUpdate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealHealth")
    float StartHealDelay = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealHealth")
    float HealModifier = 1.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    float Health = 100.0f;
    FTimerHandle HealTimerHandle;

    void HealUpdate();
};
