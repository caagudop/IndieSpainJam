// Fill out your copyright notice in the Description page of Project Settings.


#include "RamInteractuableComponent.h"

// Sets default values for this component's properties
URamInteractuableComponent::URamInteractuableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URamInteractuableComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnClicked.AddDynamic(this, &URamInteractuableComponent::OnActorClicked);
	OnSlideUpdated_Implementation(SliderValue);
}


// Called every frame
void URamInteractuableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool URamInteractuableComponent::HasReachedGoal()
{
	return SliderValue >= (GoalValue - ErrorMargin) && SliderValue <= (GoalValue + ErrorMargin);
} 

void URamInteractuableComponent::OnActorClicked(AActor* Actor, FKey ButtonPressed)
{
	if (Ram == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Ram not configured"));
		return;
	}
	Ram->UnlinkAllInteractives();
	Ram->LinkInteractive(this, true);
}

void URamInteractuableComponent::OnSlideUpdated_Implementation(float slideValue)
{
	SliderValue = FMath::Clamp(slideValue, 0.0, 1.0);
	UE_LOG(LogTemp, Display, TEXT("Percentile value is %f"), SliderValue);
	if (HasReachedGoal())
	{
		OnReachedGoal.Broadcast();
	}
}

float URamInteractuableComponent::GetSlideValue_Implementation() const
{
	return SliderValue;
}
