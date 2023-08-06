// Fill out your copyright notice in the Description page of Project Settings.


#include "TinyShooterGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UTinyShooterGameInstance::UTinyShooterGameInstance()
{
}

void UTinyShooterGameInstance::Init()
{
    Super::Init();

    if (const auto SubSystem = IOnlineSubsystem::Get())
    {
        SessionInterface = SubSystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTinyShooterGameInstance::OnCreateSessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UTinyShooterGameInstance::OnFindSessionComplete);
        }
    }
}

void UTinyShooterGameInstance::OnCreateSessionComplete(FName ServerName, bool bWasSuccessful)
{
    /*
    UE_LOG(LogTemp, Warning, TEXT("CreateSessionComplete, Succeded: %d"), bWasSuccessful);
    if (bWasSuccessful)
    {
        GetWorld()->ServerTravel("/Game/Levels/TestLevel?listen");
    }
    */
}

void UTinyShooterGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("On"));
}

void UTinyShooterGameInstance::HostServer()
{
    /*
    UE_LOG(LogTemp, Warning, TEXT("CreateServer"));

    FOnlineSessionSettings SessionSettings;
    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.bIsDedicated = false;
    SessionSettings.bIsLANMatch = true;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.bUsesPresence = true;
    SessionSettings.NumPublicConnections = 5;
    
    SessionInterface->CreateSession(0, FName("TinyShooter"), SessionSettings);
    */
}

void UTinyShooterGameInstance::JoinServer()
{
    /*
    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->bIsLanQuery = true;
    SessionSearch->MaxSearchResults = 10000;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
    
    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    */
}