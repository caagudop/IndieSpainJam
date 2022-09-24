// Fill out your copyright notice in the Description page of Project Settings.


#include "RamActor.h"

#include "RAMInteractive.h"
#include "Interactuables/RamInteractuableComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARamActor::ARamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("OriginP"));
	Origin->SetupAttachment(Root);
	Destination = CreateDefaultSubobject<USceneComponent>(TEXT("DestinationP"));
	Destination->SetupAttachment(Root);
	Selector = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector"));
	Selector->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARamActor::BeginPlay()
{
	Super::BeginPlay();

	if (Origin == nullptr || Destination == nullptr || Selector == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Ram references bad configured"));
		return;
	}
	
	// Setup
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// Sync positions
	SyncActorAxis(Origin, Selector);
	SyncActorAxis(Destination, Selector);
	// Configuration
	float distance;
	if (LockAxis == ELockAxis::X)
	{
		distance = Destination->GetComponentLocation().X - Origin->GetComponentLocation().X;
	} else
	{
		distance = Destination->GetComponentLocation().Y - Origin->GetComponentLocation().Y;
	}
	Length = GetLightAbs(distance);

	Selector->OnClicked.AddDynamic(this, &ARamActor::OnSelectorClicked);
}

// Called every frame
void ARamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSelectorDragged)
	{
		if(PlayerController->WasInputKeyJustReleased(EKeys::LeftMouseButton))
		{
			OnReleased();
		}
		UpdateSelectorToMousePosition();
	}
	UE_LOG(LogTemp, Display, TEXT("Slider Value: %f"), GetValue());
}

void ARamActor::SyncActorAxis(USceneComponent* Component, UPrimitiveComponent* From)
{
	FVector loc = Component->GetComponentLocation();
	FVector fromLoc = From->GetComponentLocation();
	if (LockAxis == ELockAxis::X)
	{
		loc.Y = fromLoc.Y;
	} else
	{
		loc.X = fromLoc.X;
	}
	loc.Z = fromLoc.Z;
	Component->SetWorldLocation(loc);
}

float ARamActor::GetLightAbs(float value)
{
	if (value < 0)
	{
		value *= -1;
	}
	return value;
}

// ---------------------------------------------------------------------------------------------------------------------

float ARamActor::GetValue()
{
	if (Origin == nullptr || Destination == nullptr || Selector == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Ram references bad configured"));
		return 0;
	}

	// TODO: cache this value
	float distance;
	if (LockAxis == ELockAxis::X)
	{
		distance = Selector->GetComponentLocation().X - Origin->GetComponentLocation().X;
	} else
	{
		distance = Selector->GetComponentLocation().Y - Origin->GetComponentLocation().Y;
	}
	distance = GetLightAbs(distance);
	return distance / Length;
}

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::UpdateInteractives()
{
	const float slideValue = GetValue();
	for (const TObjectPtr<UObject>& interactive : LinkedInteractives)
	{
		IRAMInteractive::Execute_OnSlideUpdated(interactive, slideValue);
	}
	
} // UpdateInteractives

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::LinkInteractive(UObject* interactive, bool bUpdateSlide)
{
	if (Origin == nullptr || Destination == nullptr || Selector == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Ram references bad configured"));
		return;
	}
	
	if (!UKismetSystemLibrary::DoesImplementInterface(interactive, URAMInteractive::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Object %s doesn't support RAMInteractive"), *interactive->GetName());
		return;	
	}

	LinkedInteractives.Add(interactive);
	if (bUpdateSlide)
	{
		UpdateSlide(IRAMInteractive::Execute_GetSlideValue(interactive));
	}
	
} // LinkInteractive

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::UnlinkInteractive(UObject* interactive)
{
	LinkedInteractives.Remove(interactive);
	
} // UnlinkInteractive

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::UnlinkAllInteractives()
{
	LinkedInteractives.Empty();
	
} // UnlinkAllInteractives

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::UpdateSlide(float slideValue)
{
	// Update Selector position
	const float distance = Length * slideValue;
	FVector newLocation = Selector->GetComponentLocation();;
	if (LockAxis == ELockAxis::X)
	{
		newLocation.X = Origin->GetComponentLocation().X + distance;
	}
	else
	{
		newLocation.Y = Origin->GetComponentLocation().Y + distance;
	}
	Selector->SetWorldLocation(newLocation);
	
	UpdateInteractives();
	
} // UpdateSlide

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::OnSelectorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	IsSelectorDragged = true;
	UE_LOG(LogTemp, Warning, TEXT("CLICKED!!"));
	
} // OnSelectorClicked

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::OnReleased()
{
	IsSelectorDragged = false;
	UpdateInteractives();
	
	UE_LOG(LogTemp, Warning, TEXT("RELEASED!!"));
	
} // OnReleased

// ---------------------------------------------------------------------------------------------------------------------

void ARamActor::UpdateSelectorToMousePosition()
{
	FVector location, direction;
	PlayerController->DeprojectMousePositionToWorld(location, direction);

	FHitResult Hit;
	if(GetWorld()->LineTraceSingleByChannel(Hit, location, location + (direction * 100000000000000000), ECollisionChannel::ECC_Visibility))
	{
		FVector newLocation = Selector->GetComponentLocation();
		if (LockAxis == ELockAxis::X)
		{
			newLocation.X = FMath::Clamp(Hit.ImpactPoint.X, Origin->GetComponentLocation().X, Destination->GetComponentLocation().X);
		} else
		{
			newLocation.Y = FMath::Clamp(Hit.ImpactPoint.Y, Origin->GetComponentLocation().Y, Destination->GetComponentLocation().Y);
		}
		Selector->SetWorldLocation(newLocation);
	}
}
