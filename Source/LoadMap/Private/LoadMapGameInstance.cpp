// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LoadMapGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULoadMapGameInstance::Init()
{
	AsyncDelegate.BindUObject(this, &ULoadMapGameInstance::LoadAsyncCallBack);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ULoadMapGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ULoadMapGameInstance::EndLoadingScreen);
}

void ULoadMapGameInstance::LoadMap() const
{
	UGameplayStatics::OpenLevel(this, MapName, true);
}

void ULoadMapGameInstance::AsyncLoad()
{
	AsyncDateTime = FDateTime::Now();

	LoadPackageAsync(MapName.ToString(), AsyncDelegate);
}

float ULoadMapGameInstance::GetLoadPercentage() const
{
	return GetAsyncLoadPercentage(MapName);
}

void ULoadMapGameInstance::BeginLoadingScreen(const FString& MapName)
{
	DateTime = FDateTime::Now();

	UE_LOG(LogTemp, Log, TEXT("BeginLoadingScreen => %s"), *MapName);
}

void ULoadMapGameInstance::EndLoadingScreen(UWorld* LoadedWorld) const
{
	UE_LOG(LogTemp, Log, TEXT("EndLoadingScreen => %s,use time in %fs"), *LoadedWorld->GetMapName(),
	       (FDateTime::Now()-DateTime).GetTotalSeconds());
}

void ULoadMapGameInstance::LoadAsyncCallBack(const FName& Name, UPackage* Package,
                                             EAsyncLoadingResult::Type Result) const
{
	UE_LOG(LogTemp, Log, TEXT("AsyncLoadPackage => %s,use time in %fs"), *this->MapName.ToString(),
	       (FDateTime::Now() - AsyncDateTime).GetTotalSeconds());
}
