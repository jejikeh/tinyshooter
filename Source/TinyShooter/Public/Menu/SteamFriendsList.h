// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SteamFriendsList.generated.h"

class UButton;

UCLASS()
class TINYSHOOTER_API USteamFriendsList : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
    UButton* RefreshListButton;

	virtual void NativeOnInitialized() override;
	
};
 