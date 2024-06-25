// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "ClientControlWidget.generated.h"

class ASimHUD;

/**
 * 
 */
UCLASS()
class AIRSIM_API UClientControlWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
        UClientControlWidget(const FObjectInitializer& ObjectInitializer);

		void init_(ASimHUD* hud);

		UFUNCTION()
        void startClient();

	private:
    UButton* start_client;

	ASimHUD* ownedHUD;
	
};
