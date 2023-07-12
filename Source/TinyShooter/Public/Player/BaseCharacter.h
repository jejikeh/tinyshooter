// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;

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
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* CameraBoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")    
    UTextRenderComponent* HealthTextComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    FVector2D LandedDamageVelocity = FVector2D(700.0f, 1400.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    FVector2D LandedDamageAmount = FVector2D(10.0f, 100.0f);

private:
    bool bIsRunning;
    
    void MoveForward(float Direction);
    void MoveRight(float Direction);

    void LookUp(float Amount);
    void LookRight(float Amount);

    void StartRunning();
    void StopRunning();

    void OnDeath();
    void OnHealthChanged(float Health, float ChangeAmount, const UDamageType* DamageType);

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
