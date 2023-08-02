// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "SteamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TINYSHOOTER_API USteamGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Session")
	void CreateServer();
	
};
