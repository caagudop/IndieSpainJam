// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractuableComp.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractuableComp::UInteractuableComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractuableComp::BeginPlay()
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
		Slider->OnValueChanged.AddDynamic(this, &UInteractuableComp::OnSliderValueChanged);
		Slider->OnMouseCaptureEnd.AddDynamic(this, &UInteractuableComp::OnSliderMouseCaptureEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Slider not found"));
	}
	
	// Update percentile
	UpdatePercentile();	
}


// Called every frame
void UInteractuableComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractuableComp::OpenSlider()
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

void UInteractuableComp::CloseSlider()
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

void UInteractuableComp::UpdatePercentile()
{
	UE_LOG(LogTemp, Display, TEXT("Percentile value is %f"), SliderValue);
}

void UInteractuableComp::OnSliderValueChanged(float NewValue)
{
	SliderValue = NewValue;
}

void UInteractuableComp::OnSliderMouseCaptureEnd()
{
	UpdatePercentile();
}
