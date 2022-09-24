// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkingCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWalkingCharacter::AWalkingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("My main camera"));
	MainCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0, 720.f, 0.0f);

	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->GravityScale = 8.0;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;


	tempPos = GetActorLocation();

	zPosition = tempPos.Z + 300.0f;
}

// Called when the game starts or when spawned
void AWalkingCharacter::BeginPlay()
{
	Super::BeginPlay();
	//InteractuableComp = FindComponentByClass<UInteractuableComp>();

	CanMove = true;
}

// Called every frame
void AWalkingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!scaleShow){
		//InteractuableComp->OpenSlider();
		scaleShow = true;
	}

	tempPos = GetActorLocation();

	SetActorLocation(FVector(tempPos.X + 5.f, tempPos.Y, tempPos.Z));

	tempPosCam = MainCamera->GetRelativeLocation();
	MainCamera->SetRelativeLocation(FVector(tempPosCam.X+5.f, tempPosCam.Y, tempPosCam.Z));
}

// Called to bind functionality to input
void AWalkingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void AWalkingCharacter::RestartLevel()
{
}

