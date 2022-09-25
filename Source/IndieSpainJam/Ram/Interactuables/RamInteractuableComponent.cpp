// Fill out your copyright notice in the Description page of Project Settings.


#include "RamInteractuableComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
		return;
	}
	GameInstance->RegisterPiece(PieceName, this);
	
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
		Broken = false;
		if (GameInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
			return;
		}
		GameInstance->BrokenPieces.Remove(this);
	}
}

float URamInteractuableComponent::GetSlideValue_Implementation() const
{
	return SliderValue;
}

void URamInteractuableComponent::Break()
{
	if (ErrorMargin == 1.0f)
	{
		return;
	}
	float breakValue = 0.0f;
	bool found = false;
	while (!found)
	{
		breakValue = FMath::RandRange(0.0f, 1.0f);
		found = breakValue < (GoalValue - ErrorMargin) || breakValue > (GoalValue + ErrorMargin);
	}
	OnSlideUpdated_Implementation(breakValue);
	Broken = true;
	UE_LOG(LogTemp, Display, TEXT("Broken Piece: %s"), *GetOwner()->GetName());
}

bool URamInteractuableComponent::IsBroken()
{
	return Broken;
}
