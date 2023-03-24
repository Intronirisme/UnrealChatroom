// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatServerSubsystem.h"

void UChatServerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Server world subsystem loaded"));
}

void UChatServerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UChatServerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }

    UWorld* World = Cast<UWorld>(Outer);
    return World->GetNetMode() < NM_Client;
}
