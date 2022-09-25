#include "RunnerObstacle.h"

#include "RunnerActor.h"
#include "IndieSpainJam/Ram/RAMInteractive.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// ---------------------------------------------------------------------------------------------------------------------

ARunnerObstacle::ARunnerObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CollisionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionTrigger);

	CollisionTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	
} // ARunnerObstacle

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerObstacle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetObstacleActive(false);
	
} // PostInitializeComponents

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerObstacle::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	const FVector offset = deltaSeconds * 100.f * Speed * GetActorForwardVector();
	AddActorWorldOffset(offset, true);
	
} // Tick

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerObstacle::SetObstacleActive(bool bActive)
{
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);
	SetActorTickEnabled(bActive);
	
} // SetObstacleActive

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerObstacle::NotifyHit(UPrimitiveComponent* myComp, AActor* other, UPrimitiveComponent* otherComp,
	bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
	Super::NotifyHit(myComp, other, otherComp, bSelfMoved, hitLocation, hitNormal, normalImpulse, hit);

	if (!UKismetSystemLibrary::DoesImplementInterface(other, URAMInteractive::StaticClass()))
	{
		return;
	}
	
	SetActorEnableCollision(false);
	const float runnerSlide = IRAMInteractive::Execute_GetSlideValue(other);
	const bool bSuccess = runnerSlide >= 0.01 * SlideThreshold && bFailIfBelowThreshold;
	OnObstacleHit.Broadcast(this, bSuccess);

	if (ARunnerActor* runnerActor = Cast<ARunnerActor>(other))
	{
	    runnerActor->OnFailed();
	}
	
} // NotifyHit

// ---------------------------------------------------------------------------------------------------------------------