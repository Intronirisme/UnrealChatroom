// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChatSubsystem.h"

void UPlayerChatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Player subsystem loaded"));
}

void UPlayerChatSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UPlayerChatSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}
