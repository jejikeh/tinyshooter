// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevDamageActor.generated.h"

UCLASS()
class TINYSHOOTER_API ADevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    ADevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    float Radius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    FColor SphereColor = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    float Damage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    bool bDoFullDamage = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    TSubclassOf<UDamageType> DamageType;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
