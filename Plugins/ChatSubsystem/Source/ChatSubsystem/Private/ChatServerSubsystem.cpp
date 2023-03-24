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

bool UChatServerSubsystem::StartListener(const FString& BindAddress, int32 Port)
{
    if (FIPv4Endpoint::FromHostAndPort(FString::Printf(TEXT("%s:%i"), *BindAddress, Port), _serverEndPoint))
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Listening on %s:%i"), *BindAddress, Port));
        FSocket* commSocket = FTcpSocketBuilder(*UChatServerSubsystem::DefaultSocketName).AsReusable().BoundToEndpoint(_serverEndPoint).Listening(8);
        _chatSocket = TUniquePtr<FSocket>(commSocket);
        return true;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Invalid ip format"));
    }
    return false;
}