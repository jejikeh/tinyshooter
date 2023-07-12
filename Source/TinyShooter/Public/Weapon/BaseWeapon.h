// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class TINYSHOOTER_API ABaseWeapon : public AActor
{
    GENERATED_BODY()
    
public: 
    ABaseWeapon();

    virtual void Shoot();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UStaticMeshComponent* WeaponMesh;

    virtual void BeginPlay() override;
};
