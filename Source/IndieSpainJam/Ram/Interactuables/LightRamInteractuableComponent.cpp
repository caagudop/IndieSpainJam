// Fill out your copyright notice in the Description page of Project Settings.


#include "LightRamInteractuableComponent.h"

#include "Components/DirectionalLightComponent.h"

void ULightRamInteractuableComponent::BeginPlay()
{
	Diff = MaxIntensity - MinIntensity;
	
	Super::BeginPlay();
}

void ULightRamInteractuableComponent::OnSlideUpdated_Implementation(float slideValue)
{
	Super::OnSlideUpdated_Implementation(slideValue);
	
	if (DirectionalLight == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("DirectionalLight not configured"));
		return;
	}
	DirectionalLight->GetComponent()->SetIntensity(MinIntensity + Diff * SliderValue);
}
