// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TINYSHOOTER_API ABulletProjectile : public AActor
{
    GENERATED_BODY()
    
public: 
    ABulletProjectile();

    void SetShotDirection(const FVector& Direction);
    void SetDamageAmount(float Damage);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
    float DamageAmount = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
    float DamageRadius = 1.0f;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

private:
    FVector ShotDirection;

};
