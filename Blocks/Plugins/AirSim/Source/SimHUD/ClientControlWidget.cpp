// Fill out your copyright notice in the Description page of Project Settings.


#include "SimHUD/ClientControlWidget.h"

#ifndef SimHUD
#define SimHUD
#include "SimHUD.h"
#endif // !SimHUD


UClientControlWidget::UClientControlWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UClientControlWidget::init_(ASimHUD* hud)
{
    ownedHUD = hud;

    start_client = dynamic_cast<UButton*>(GetWidgetFromName("StartClient"));

    if (start_client) {
        start_client->OnClicked.AddDynamic(this, &UClientControlWidget::startClient);
    }
}

void UClientControlWidget::startClient()
{
    if (ownedHUD)
    {
        ownedHUD->createClientForThread();
    }
}
