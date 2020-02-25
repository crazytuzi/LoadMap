// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoadMapGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOADMAP_API ULoadMapGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMap() const;

	UFUNCTION(BlueprintCallable)
	void AsyncLoad();

	UFUNCTION(BlueprintCallable)
	float GetLoadPercentage() const;

	void BeginLoadingScreen(const FString& MapName);

	void EndLoadingScreen(UWorld* LoadedWorld) const;

	void LoadAsyncCallBack(const FName& Name, UPackage* Package, EAsyncLoadingResult::Type Result) const;

private:

	FDateTime AsyncDateTime;

	FDateTime DateTime;

	FLoadPackageAsyncDelegate AsyncDelegate;

	const FName MapName = "/Game/Maps/FirstPersonExampleMap";
};
