// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RamInteractuableComponent.h"
#include "ScaleRamInteractuableComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class INDIESPAINJAM_API UScaleRamInteractuableComponent : public URamInteractuableComponent
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnSlideUpdated_Implementation(float slideValue) override;
	
public:
	UPROPERTY(EditAnywhere)
	FVector MinScale = FVector(0,0, 0);
	UPROPERTY(EditAnywhere)
	FVector MaxScale = FVector(1,1, 1);

private:
	float XDiff;
	float YDiff;
	float ZDiff;
};
