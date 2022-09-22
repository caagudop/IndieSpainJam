// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactuable.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

class USlider;
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
	
	// Create widget
	if (!WidgetBlueprint)
	{
		UE_LOG(LogTemp, Error, TEXT("Widget Blueprint not selected"));
		return;
	}
	WidgetRef = CreateWidget<UUserWidget>(GetWorld(), WidgetBlueprint);
	WidgetRef->AddToViewport();
	WidgetRef->SetVisibility(ESlateVisibility::Hidden);
	USlider* Slider = Cast<USlider>(WidgetRef->GetWidgetFromName(FName(TEXT("Slider_0"))));
	if (Slider != nullptr)
	{
		Slider->SetValue(SliderValue);
		Slider->OnValueChanged.AddDynamic(this, &AInteractuable::OnSliderValueChanged);
		Slider->OnMouseCaptureEnd.AddDynamic(this, &AInteractuable::OnSliderMouseCaptureEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Slider not found"));
	}
	
	// Update percentile
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

void AInteractuable::OnSliderValueChanged(float NewValue)
{
	SliderValue = NewValue;
}

void AInteractuable::OnSliderMouseCaptureEnd()
{
	UpdatePercentile();
}