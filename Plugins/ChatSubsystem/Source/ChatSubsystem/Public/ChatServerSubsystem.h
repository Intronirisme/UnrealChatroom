// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Networking.h"
#include "ChatServerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CHATSUBSYSTEM_API UChatServerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	static inline FString DefaultSocketName = FString("ChatSubsystem_TCP");;

public:

	UFUNCTION(BlueprintCallable, Category = ChatSubsystem)
		bool StartListener(const FString& BindAddress, int32 Port);

private:

	TUniquePtr<FSocket> _chatSocket;
	FIPv4Endpoint _serverEndPoint;
};
