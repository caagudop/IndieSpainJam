// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkingPawn.h"


// Sets default values
AWalkingPawn::AWalkingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AWalkingPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWalkingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(GetActorForwardVector(), MovementValue);
}

// Called to bind functionality to input
void AWalkingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

