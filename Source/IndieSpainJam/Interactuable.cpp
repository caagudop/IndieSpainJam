// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactuable.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractuable::AInteractuable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractuable::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UpdatePercentile();
}

// Called every frame
void AInteractuable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractuable::OpenSlider()
{
	if (WidgetRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetRef is null"));	
		return;
	}
	WidgetRef->SetVisibility(ESlateVisibility::Visible);	
	PlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, WidgetRef, EMouseLockMode::LockAlways, false);
}

void AInteractuable::CloseSlider()
{
	if (WidgetRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetRef is null"));	
		return;
	}
	WidgetRef->SetVisibility(ESlateVisibility::Hidden);	
	PlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
}

void AInteractuable::UpdatePercentile()
{
	UE_LOG(LogTemp, Display, TEXT("Percentile value is %f"), SliderValue);
}
