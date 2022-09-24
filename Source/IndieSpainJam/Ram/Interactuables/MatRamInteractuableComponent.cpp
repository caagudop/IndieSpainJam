// Fill out your copyright notice in the Description page of Project Settings.


#include "MatRamInteractuableComponent.h"

void UMatRamInteractuableComponent::BeginPlay()
{
	Diff = maxValue - minValue;
	
	Super::BeginPlay();
}

void UMatRamInteractuableComponent::OnSlideUpdated_Implementation(float slideValue)
{
	if (MaterialInstanceDynamic == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MaterialInstaceDynamic not configured in %s"), *GetOwner()->GetName());
		return;
	}
	MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, minValue + Diff * slideValue);
}
