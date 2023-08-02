// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TinyShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API UTinyShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
   UTinyShooterGameInstance();
   
protected:
    TSharedPtr<FOnlineSessionSearch> SessionSearch;
    
    IOnlineSessionPtr SessionInterface;
    
    virtual void Init() override;

    void OnCreateSessionComplete(FName ServerName, bool bWasSuccessful);
    void OnFindSessionComplete(bool bWasSuccessful);
    
    UFUNCTION(BlueprintCallable)
    void HostServer();
    
    UFUNCTION(BlueprintCallable)
    void JoinServer();
};
