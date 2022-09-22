// Fill out your copyright notice in the Description page of Project Settings.


#include "ChairInteractuableComp.h"

void UChairInteractuableComp::BeginPlay()
{
	XDiff = MaxScale.X - MinScale.X;
	YDiff = MaxScale.Y - MinScale.Y;
	ZDiff = MaxScale.Z - MinScale.Z;
	
	Super::BeginPlay();
}

void UChairInteractuableComp::UpdatePercentile()
{
	const FVector NewScale = FVector(
		MinScale.X + XDiff * SliderValue,
		MinScale.Y + YDiff * SliderValue,
		MinScale.Z + ZDiff * SliderValue);
	GetOwner()->SetActorScale3D(NewScale);
	Super::UpdatePercentile();
}