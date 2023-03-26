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

    // Close the socket after unloading subsystem
    // It avoid errors like "port already in use" caused by remaining socket
    if (_chatSocket != NULL)
    {
        _chatSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(_chatSocket.Get());
    }
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
        
        // Set a timer to call AcceptConnections() every  1s in loop
        GetWorld()->GetTimerManager().SetTimer(_listenerHandle, this, &UChatServerSubsystem::AcceptConnections, 1.0f, true);
        return true;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Invalid ip format"));
    }
    return false;
}

void UChatServerSubsystem::AcceptConnections()
{
    // Don't do anything if there is no socket.
    if (_chatSocket == NULL) return;

    bool pending;

    if (_chatSocket->HasPendingConnection(pending) && pending)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Entering client"));

        // We create an FInternetAddr to hold our client IP:port
        TSharedRef<FInternetAddr> remoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

        // We accept the client
        FSocket* incomingCLient = _chatSocket->Accept(*remoteAddress, FString::Printf(TEXT("PLayer chat %i"), _clientSockets.Num()));
        if (incomingCLient != NULL) _clientSockets.Add(incomingCLient);
    }
    else GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Waiting for connections"));

}
