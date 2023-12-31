// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/BaseWeapon.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;
class UWeaponComponent;

UCLASS()
class TINYSHOOTER_API ABaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABaseCharacter(const FObjectInitializer& ObjectInitializer);
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    float HealthFromComponent;

    bool bIsDead = false;

    UFUNCTION(Client, Reliable)
    void Client_SetRoundInfrormationToGameState(float RoundTime, int32 Round);
    void Client_SetRoundInfrormationToGameState_Implementation(float RoundTime, int32 Round);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY()
    TSoftClassPtr<ABaseWeapon> Weapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* CameraBoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")    
    UTextRenderComponent* HealthTextComponent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    FVector2D LandedDamageVelocity = FVector2D(700.0f, 1400.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    FVector2D LandedDamageAmount = FVector2D(10.0f, 100.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UWeaponComponent* WeaponComponent;

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_StartShoot();
    bool Server_StartShoot_Validate();
    void Server_StartShoot_Implementation();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_StopShoot();
    bool Server_StopShoot_Validate();
    void Server_StopShoot_Implementation();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_NextWeapon();
    bool Server_NextWeapon_Validate();
    void Server_NextWeapon_Implementation();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_ReloadWeapon();
    bool Server_ReloadWeapon_Validate();
    void Server_ReloadWeapon_Implementation();

    UFUNCTION(NetMulticast, Reliable, WithValidation)
    void Server_Death();
    bool Server_Death_Validate();
    void Server_Death_Implementation();

    UFUNCTION(NetMulticast, Reliable, WithValidation)
    void Server_UpdateText(float Health);
    bool Server_UpdateText_Validate(float Health);
    void Server_UpdateText_Implementation(float Health);

    UFUNCTION(NetMulticast, Reliable)
    void Server_Multicast_PlayWeaponShootAnimation();
    void Server_Multicast_PlayWeaponShootAnimation_Implementation();
    
    UFUNCTION(NetMulticast, Reliable)
    void Server_Multicast_SetNextWeaponAnimRefs();
    void Server_Multicast_SetNextWeaponAnimRefs_Implementation();
    
    UFUNCTION(NetMulticast, Reliable)
    void Server_Multicast_NextWeaponAnimPlay();
    void Server_Multicast_NextWeaponAnimPlay_Implementation();

    UFUNCTION(NetMulticast, Reliable, WithValidation)
    void Server_PlayWeaponReloadAnimation();
    bool Server_PlayWeaponReloadAnimation_Validate();
    void Server_PlayWeaponReloadAnimation_Implementation();

private:
    UPROPERTY(Replicated)
    bool bIsRunning;
    
    void MoveForward(float Direction);
    void MoveRight(float Direction);

    void LookUp(float Amount);
    void LookRight(float Amount);

    void StartShoot();
    void StopShoot();
    void NextWeapon();
    void Reload();

    void StartRunning();
    void StopRunning();

    void OnDeath();
    void OnHealthChanged(float Health, float ChangeAmount, const UDamageType* DamageType);

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
