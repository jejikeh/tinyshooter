// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CustomCharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Components/WeaponComponent.h"

struct FDamageEvent;

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    CameraBoom->SetupAttachment(GetMesh(), "head");
    CameraBoom->bUsePawnControlRotation = true;
        
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    CameraComponent->bUsePawnControlRotation = false;

    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    OnHealthChanged(HealthComponent->GetCurrentHealth(), HealthComponent->GetCurrentHealth(), nullptr);
    HealthComponent->OnDeathEvent.AddUObject(this, &ABaseCharacter::OnDeath);
    HealthComponent->OnHealthChangeEvent.AddUObject(this, &ABaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ABaseCharacter::OnGroundLanded);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("Move Right / Left", this, &ABaseCharacter::MoveRight);
    
    PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &ABaseCharacter::LookUp);
    PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &ABaseCharacter::LookRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ABaseCharacter::Jump);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABaseCharacter::StartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ABaseCharacter::StopRunning);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::Shoot);
}

bool ABaseCharacter::IsRunning()
{
    return bIsRunning && !GetVelocity().IsZero();
}

void ABaseCharacter::MoveForward(float Direction)
{
    AddMovementInput(GetActorForwardVector(), Direction);
}

void ABaseCharacter::MoveRight(float Direction)
{
    AddMovementInput(GetActorRightVector(), Direction);
}

void ABaseCharacter::LookUp(float Amount)
{
    AddControllerPitchInput(Amount);
}

void ABaseCharacter::LookRight(float Amount)
{
    AddControllerYawInput(Amount);
}

void ABaseCharacter::StartRunning()
{
    bIsRunning = true;
}

void ABaseCharacter::StopRunning()
{
    bIsRunning = false;
}

void ABaseCharacter::OnDeath() 
{
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    GetCharacterMovement()->DisableMovement();

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ABaseCharacter::OnHealthChanged(float Health, float ChangeAmount, const UDamageType *DamageType)
{
    const auto HealthString = FString::Printf(TEXT("%.0f"), Health);
    HealthTextComponent->SetText(FText::FromString(HealthString));
}

void ABaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto LandVelocityZ = GetCharacterMovement()->Velocity.Z;
    if (-LandVelocityZ < LandedDamageVelocity.X)
    {
        return;
    }

    const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamageAmount, -LandVelocityZ);
    TakeDamage(FallDamage, FDamageEvent{}, nullptr, nullptr);
}