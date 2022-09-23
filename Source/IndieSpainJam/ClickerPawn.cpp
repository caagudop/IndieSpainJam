// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerPawn.h"

// Sets default values
AClickerPawn::AClickerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//OnClicked.AddUnique(&AClickerPawn::ActionOnClicked);
}

// Called when the game starts or when spawned
void AClickerPawn::BeginPlay()
{
	Super::BeginPlay();
	InteractuableComp = FindComponentByClass<UInteractuableComp>();
}

// Called every frame
void AClickerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClickerPawn::ActionOnClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("uwu"));
}

void AClickerPawn::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("++++++++++"));
	
	if (InteractuableComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractuableComp not found"));
		return;
	}
	InteractuableComp->OpenSlider();
}


