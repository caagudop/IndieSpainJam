// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleRamInteractuableComponent.h"

void UScaleRamInteractuableComponent::BeginPlay()
{
	XDiff = MaxScale.X - MinScale.X;
	YDiff = MaxScale.Y - MinScale.Y;
	ZDiff = MaxScale.Z - MinScale.Z;
	
	Super::BeginPlay();
}

void UScaleRamInteractuableComponent::UpdatePercentile(float value)
{
	Super::UpdatePercentile(value);
	const FVector NewScale = FVector(
		MinScale.X + XDiff * SliderValue,
		MinScale.Y + YDiff * SliderValue,
		MinScale.Z + ZDiff * SliderValue);
	GetOwner()->SetActorScale3D(NewScale);
}