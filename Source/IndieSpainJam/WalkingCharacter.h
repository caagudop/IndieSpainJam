// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractuableComp.h"
#include "WalkingCharacter.generated.h"

UCLASS()
class INDIESPAINJAM_API AWalkingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWalkingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* MainCamera;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UCameraComponent* GetMainCamera() const{
		return MainCamera;
	}

	void RestartLevel();

	
private:
	bool scaleShow = false;
	UPROPERTY() UInteractuableComp* InteractuableComp;
	float zPosition;
	FVector tempPos = FVector();
	FVector tempPosCam = FVector();
	bool CanMove;

};
