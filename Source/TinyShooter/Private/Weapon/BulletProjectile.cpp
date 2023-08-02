// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ABulletProjectile::ABulletProjectile()
{
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(1.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->SetNetAddressable();
    MovementComponent->SetIsReplicated(true); 

    bReplicates = true;
    bAlwaysRelevant = true;
}

void ABulletProjectile::BeginPlay()
{
    Super::BeginPlay();
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnHit);
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SetLifeSpan(4.0f);
}

void ABulletProjectile::SetShotDirection(const FVector& Direction) 
{
    ShotDirection = Direction;
}

void ABulletProjectile::SetDamageAmount(float Damage)
{
    DamageAmount = Damage;
}

void ABulletProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
    MovementComponent->StopMovementImmediately();
    
    UGameplayStatics::ApplyDamage(
        OtherActor,
        DamageAmount,
        nullptr,
        this,
        UDamageType::StaticClass());

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Yellow, false, 5.0f);

    Destroy();
}