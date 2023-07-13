// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class USoundCue;

UCLASS()
class TINYSHOOTER_API ABaseWeapon : public AItem
{
    GENERATED_BODY()
    
public: 
    ABaseWeapon();

    virtual void Shoot();
    virtual void MakeShootEffect();
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    FName MuzzleSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    float TraceMaxDistance = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USoundCue* FireSound;

    virtual void BeginPlay() override;

    void ApplyDamage(const FHitResult& HitResult);
    AController* GetPlayerController();
};
