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
    HealthComponent->SetNetAddressable();
    HealthComponent->SetIsReplicated(true); 

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
    WeaponComponent->SetNetAddressable();
    WeaponComponent->SetIsReplicated(true);
}

void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    OnHealthChanged(HealthComponent->GetCurrentHealth(), HealthComponent->GetCurrentHealth(), nullptr);
    HealthComponent->OnDeathEvent.AddUObject(this, &ABaseCharacter::OnDeath);
    HealthComponent->OnHealthChangeEvent.AddUObject(this, &ABaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ABaseCharacter::OnGroundLanded);
}

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

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::StartShoot);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABaseCharacter::StopShoot);

    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &ABaseCharacter::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABaseCharacter::Reload);
}

bool ABaseCharacter::IsRunning()
{
    return bIsRunning && !GetVelocity().IsZero();
}

bool ABaseCharacter::Server_StartShoot_Validate()
{
    return true;
}

// NOTE(): ownership in other actors. BaseWeapon replication and ownership issue
void ABaseCharacter::Server_StartShoot_Implementation()
{
    WeaponComponent->StartShoot();
    Server_Multicast_PlayWeaponShootAnimation();
}

bool ABaseCharacter::Server_StopShoot_Validate()
{
    return true;
}

void ABaseCharacter::Server_StopShoot_Implementation()
{
    WeaponComponent->StopShoot();
}

bool ABaseCharacter::Server_NextWeapon_Validate()
{
    return true;
}

void ABaseCharacter::Server_NextWeapon_Implementation()
{
    Server_Multicast_SetNextWeaponAnimRefs();
    WeaponComponent->Server_NextWeapon();
    Server_Multicast_NextWeaponAnimPlay();
}

/**
 * @brief Multicast call to set the animation refs on the all clients
 */
void ABaseCharacter::Server_Multicast_SetNextWeaponAnimRefs_Implementation()
{
    WeaponComponent->SetNextWeaponAnimRefs();
}

void ABaseCharacter::Server_Multicast_NextWeaponAnimPlay_Implementation()
{
    WeaponComponent->PlayWeaponEquipAnimation();
}

bool ABaseCharacter::Server_Death_Validate()
{
    return true;
}

void ABaseCharacter::Server_Death_Implementation()
{
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    GetCharacterMovement()->DisableMovement();

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }

    bIsDead = true;
}

bool ABaseCharacter::Server_UpdateText_Validate(float Health)
{
    return true;
}

void ABaseCharacter::Server_UpdateText_Implementation(float Health)
{
    const auto HealthString = FString::Printf(TEXT("%.0f"), Health);
    HealthTextComponent->SetText(FText::FromString(HealthString));
    HealthFromComponent = Health;
}

bool ABaseCharacter::Server_ReloadWeapon_Validate()
{
    return true;
}

void ABaseCharacter::Server_ReloadWeapon_Implementation()
{
    WeaponComponent->Reload();
    Server_PlayWeaponReloadAnimation();
}

void ABaseCharacter::Server_Multicast_PlayWeaponShootAnimation_Implementation()
{
    WeaponComponent->PlayShootAnimation();
}

bool ABaseCharacter::Server_PlayWeaponReloadAnimation_Validate()
{
    return true;
}

void ABaseCharacter::Server_PlayWeaponReloadAnimation_Implementation()
{
    WeaponComponent->PlayReloadAnimation();
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

void ABaseCharacter::StartShoot()
{
    if (!HasAuthority())
    {
        Server_StartShoot();
    }
    else
    {
        WeaponComponent->StartShoot();
        Server_Multicast_PlayWeaponShootAnimation();
    }
}

void ABaseCharacter::StopShoot()
{
    if (!HasAuthority())
    {
        Server_StopShoot();
    }
    else
    {
        WeaponComponent->StopShoot();
    }
}

void ABaseCharacter::NextWeapon()
{
    if (!HasAuthority())
    {
        Server_NextWeapon();
    }
    else
    {
        // or its bad to use Implementation
        Server_NextWeapon_Implementation();
    }
}

void ABaseCharacter::Reload()
{
    if (!HasAuthority())
    {
        Server_ReloadWeapon();
    }
    else
    {
        Server_ReloadWeapon_Implementation();
    }
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
    Server_Death();
}

void ABaseCharacter::OnHealthChanged(float Health, float ChangeAmount, const UDamageType *DamageType)
{
    Server_UpdateText(Health);
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