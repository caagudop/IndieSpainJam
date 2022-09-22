// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactuable.h"
#include "ChairInteractuable.generated.h"

/**
 * 
 */
UCLASS()
class INDIESPAINJAM_API AChairInteractuable : public AInteractuable
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void UpdatePercentile() override;

	UPROPERTY(EditAnywhere)
	FVector MinScale = FVector(0,0, 0);
	UPROPERTY(EditAnywhere)
	FVector MaxScale = FVector(1,1, 1);

private:
	float XDiff;
	float YDiff;
	float ZDiff;
};
