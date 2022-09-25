#include "RunnerActor.h"

#include "Components/BoxComponent.h"

// ---------------------------------------------------------------------------------------------------------------------

ARunnerActor::ARunnerActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetCollisionObjectType(ECC_Pawn);
	
} // ARunnerActor

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerActor::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	SetCurrentSlide(CurrentSlide);
	
} // OnConstruction

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerActor::SetCurrentSlide(float slideValue)
{
	CurrentSlide = FMath::Clamp(slideValue, 0.f, 1.f);
	
	const float slideToScale = FMath::Lerp(MinSize, MaxSize, CurrentSlide);
	SetActorScale3D(slideToScale * FVector::OneVector);
	
} // SetCurrentSlide

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerActor::OnSlideUpdated_Implementation(float slideValue)
{
	SetCurrentSlide(slideValue);
	
} // OnSlideUpdated_Implementation

// ---------------------------------------------------------------------------------------------------------------------

float ARunnerActor::GetSlideValue_Implementation() const
{
	return CurrentSlide;
	
} // GetSlideValue_Implementation

// ---------------------------------------------------------------------------------------------------------------------
