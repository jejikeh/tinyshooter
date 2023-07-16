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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	UProjectileMovementComponent* MovementComponent;

private:
	FVector ShotDirection;

};
