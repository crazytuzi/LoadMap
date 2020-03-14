// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadMapGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MoviePlayer.h"
#include "UserWidget.h"

void ULoadMapGameInstance::Init()
{
	Super::Init();

	bIsFirstLevel = true;

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

	FLoadingScreenAttributes LoadingScreenAttributes;

	LoadingScreenAttributes.bMoviesAreSkippable = false;

	LoadingScreenAttributes.bWaitForManualStop = false;

	LoadingScreenAttributes.PlaybackType = MT_Normal;

	if (bIsFirstLevel)
	{
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = false;

		LoadingScreenAttributes.MoviePaths.Add(TEXT("Default_Startup"));

		bIsFirstLevel = false;
	}
	else
	{
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;

		const auto LoadingWidgetClass = LoadClass<UUserWidget>(GetTransientPackage(),
		                                                       TEXT(
			                                                       "/Game/Blueprints/WBP_LoadingScreen.WBP_LoadingScreen_C"));

		if (LoadingWidgetClass != nullptr)
		{
			auto LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);

			if (LoadingWidget != nullptr)
			{
				const auto LoadingTakeWidget = LoadingWidget->TakeWidget();

				LoadingScreenAttributes.WidgetLoadingScreen = LoadingTakeWidget;
			}
		}
	}

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void ULoadMapGameInstance::EndLoadingScreen(UWorld* LoadedWorld) const
{
	UE_LOG(LogTemp, Log, TEXT("EndLoadingScreen => %s,use time in %fs"), *LoadedWorld->GetMapName(),
	       (FDateTime::Now()-DateTime).GetTotalSeconds());

	if (GetMoviePlayer()->IsMovieCurrentlyPlaying())
	{
		GetMoviePlayer()->StopMovie();
	}
}

void ULoadMapGameInstance::LoadAsyncCallBack(const FName& Name, UPackage* Package,
                                             EAsyncLoadingResult::Type Result) const
{
	UE_LOG(LogTemp, Log, TEXT("AsyncLoadPackage => %s,use time in %fs"), *this->MapName.ToString(),
	       (FDateTime::Now() - AsyncDateTime).GetTotalSeconds());
}
